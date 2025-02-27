
#include "grammar_core.h"

#include <fstream>
#include <streambuf>
#include "jsonxx.h"

using namespace jsonxx;

Grammar* main_grammar = nullptr;

int add_rule_to_mapping(Grammar* grammar, string rulename){
    if (grammar->rule_mapping.count(rulename) > 0) return grammar->rule_mapping.at(rulename);
    else {grammar->rule_mapping[rulename] = (int)(grammar->rule_mapping.size() + 1); return grammar->rule_mapping.at(rulename);}
}

rule_tags add_tags(Grammar* grammar, vector<string> tags){
    auto res = rule_tags();
    auto k = 0;
    for (auto t : tags){
        if (grammar->tag_mapping.count(t) > 0) res[k] = grammar->tag_mapping.at(t);
        else { grammar->tag_mapping[t] = (int)(grammar->tag_mapping.size() + 1); res[k] = grammar->tag_mapping.at(t);}
        k++;
    }
    return res;
}

int tag_to_mapping(Grammar* grammar, string tag) {
    if (grammar->tag_mapping.count(tag) > 0) { return grammar->tag_mapping[tag]; }
    else {
        //printf("[TAG->MAPPING] [ERROR] tag not found : %s\n", tag.c_str());
        return -1;
    }
}

string mapping_to_tag(Grammar* grammar, int tag) {
    for( auto&& pair : grammar->tag_mapping ){
        if (pair.second == tag) return pair.first;
    }
//    printf("[MAPPING->TAG] [ERROR] tag not found : %d\n", tag);
    return "";
}

bool is_tag_invert(Grammar* grammar, int tag){
    auto s_tag = mapping_to_tag(grammar, tag);
    if (contains(s_tag, "inv_")) return true;
    else return false;
}

int invert_tag(Grammar* grammar, int tag){
    auto s_tag = mapping_to_tag(grammar, tag);
    if (contains(s_tag, "inv_")) {
        return tag_to_mapping(grammar, s_tag.substr(4));
    }
    else{
        auto res = tag_to_mapping(grammar, "inv_" + s_tag);
        if (res == -1) { auto temp = add_tags(grammar, {"inv_" + s_tag}); res = temp[0]; }
        return res;
    }
}


Grammar* get_grammar(string filename){
    if (main_grammar == nullptr){
        auto res = new Grammar();
        
        ifstream t(filename);
        string str;
        t.seekg(0, std::ios::end);  str.reserve(t.tellg()); t.seekg(0, std::ios::beg);
        str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        
        Object o;
        o.parse(str);
        //cout << o.json() << endl;
        
        assert(o.has<String>("grammar_name"));
        assert(o.has<Number>("seed"));
        assert(o.has<Number>("framerate"));
        assert(o.has<Array>("rules"));
        assert(o.has<Array>("bbox"));
        assert(o.has<Boolean>("dry_run"));
        
        res->name = o.get<String>("grammar_name");
        auto g_seed = o.get<Number>("seed");
        if (g_seed != -1) res->seed = o.get<Number>("seed");
        else {
            std::random_device rd;     // only used once to initialise (seed) engine
            std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
            std::uniform_int_distribution<int> uni(0, INT_MAX); // guaranteed unbiased
            auto random_integer = uni(rng);
            res->seed = random_integer;
            std::cout << "[GRAMMAR] Random seed initialized to " << random_integer << std::endl;
        }
        uint64_t initseq = ym_hash_uint64(res->seed);
        uint64_t initstate = ym_hash_uint64(res->seed * 3202034522624059733ull + 1ull);
        ym_rng_init(&res->rn, initstate, initseq);
        
        auto bbox_arr = o.get<Array>("bbox");
        res->output_bbox = ym_range2r({(double)bbox_arr.get<Number>(0), (double)bbox_arr.get<Number>(1)},
                                      {(double)bbox_arr.get<Number>(2), (double)bbox_arr.get<Number>(3)});
        
        res->dry_run = o.get<Boolean>("dry_run");
        
        auto r_arr = o.get<Array>("rules");
        for (auto i = 0; i < r_arr.size(); i++){
            auto rule_json = r_arr.get<Object>(i);
            auto rule = new Rule();
            
            rule->rule_name = add_rule_to_mapping(res, rule_json.get<String>("rule_name"));
            //dirty, so dirty. FIX this
            rule->rule_name_str = rule_json.get<String>("rule_name");
            
            auto json_mtags = vector<string>();
            auto mt_arr = rule_json.get<Array>("matching_tags");
            for (auto j = 0; j < mt_arr.size(); j++) json_mtags.push_back(mt_arr.get<String>(j));
            rule->matching_tags = add_tags(res, json_mtags);
            
            auto json_ptags = vector<string>();
            auto pt_arr = rule_json.get<Array>("produced_tags");
            for (auto j = 0; j < pt_arr.size(); j++) json_ptags.push_back(pt_arr.get<String>(j));
            rule->produced_tags = add_tags(res, json_ptags);
            
            auto s_init_value = rule_json.get<String>("init_value");
            auto init_value = add_tags(res, {s_init_value});
            
            if (rule_json.get<String>("operator") == "split")
                rule->op = Operator(op_split, init_value[0]);
            else if (rule_json.get<String>("operator") == "place")
                rule->op = Operator(op_place, init_value[0]);
            else if (rule_json.get<String>("operator") == "init")
                rule->op = Operator(op_init, init_value[0]);
            else if (rule_json.get<String>("operator") == "time_init")
                rule->op = Operator(op_time_init, init_value[0]);
            else if (rule_json.get<String>("operator") == "time_slice")
                rule->op = Operator(op_time_slice, init_value[0]);
            
            else if (rule_json.get<String>("operator") == "affine")
                rule->op = Operator(op_affine, init_value[0]);
            else if (rule_json.get<String>("operator") == "rotation")
                rule->op = Operator(op_affine_rot, init_value[0]);
            else if (rule_json.get<String>("operator") == "scale")
                rule->op = Operator(op_affine_scale, init_value[0]);
            else if (rule_json.get<String>("operator") == "translation")
                rule->op = Operator(op_affine_tran, init_value[0]);
            else if (rule_json.get<String>("operator") == "rot_scale")
                rule->op = Operator(op_affine_rot_scale, init_value[0]);
            else if (rule_json.get<String>("operator") == "rot_tran")
                rule->op = Operator(op_affine_rot_tran, init_value[0]);
            else if (rule_json.get<String>("operator") == "scale_tran")
                rule->op = Operator(op_affine_scale_tran, init_value[0]);
            
            else if (rule_json.get<String>("operator") == "attribute")
                rule->op = Operator(op_attribute, init_value[0]);
            
            else if (rule_json.get<String>("operator") == "move_towards")
                rule->op = Operator(op_move_towards, init_value[0]);
            else
                rule->op = Operator(op_default, -1);
            
            auto json_params = rule_params(INFINITY);
            auto p_arr = rule_json.get<Array>("parameters");
            for (auto j = 0; j < p_arr.size(); j++) json_params[j] = p_arr.get<Number>(j);
            rule->parameters = json_params;
            
            res->rules.push_back(rule);
        }
        
        res->framerate = (double) o.get<Number>("framerate");
        
        main_grammar = res;
        return main_grammar;
    }
    else return main_grammar;
}

vector<Rule*> get_inits(Grammar* g){
    auto res = vector<Rule*>();
    if (g != nullptr){
        for (auto r : g->rules) if (r->op.operator_name == op_init || r->op.operator_name == op_time_init) res.push_back(r);
    }
    return res;
}

vector<Rule*> get_rules(Grammar* g){
    if (g != nullptr) return g->rules;
    return vector<Rule*>();
}

Rule* matching_init(){
    auto grammar = get_grammar(grammar_filename);
    auto inits = get_inits(grammar);
    if (not inits.empty())
        return inits[(int)(ym_rng_nextf(&grammar->rn) * inits.size())];
    else {
//        printf("Didn't find any init rule for matching\n");
        return nullptr;
    }
}

pair<PartitionShapeGroup, Rule*> matching(const ShapeGroup& active_shapes){
    auto grammar = get_grammar(grammar_filename);
    //matching of the shapes
    auto matched_shapes = matching_shapes(active_shapes);
    //matching of the rule
    if (not matched_shapes.match.empty()){
        auto rule_to_apply = matching_rule(matched_shapes.match);
        if (rule_to_apply != nullptr){
            return make_pair(matched_shapes, rule_to_apply);
        }
    }
//    printf("Didn't find any rule for matching\n");
    return pair<PartitionShapeGroup, Rule*>(PartitionShapeGroup(), nullptr);
}

pair<PartitionShapeGroup, Rule*> matching_slice(Grammar* g, const ShapeGroup& active_shapes, const map<Shape*, TimeManager::NodeTimeLine*>& shape_map){
    //matching of the shapes
    auto matched_shapes = matching_shapes(active_shapes, false, shape_map);
    //matching of the rule
    if (not matched_shapes.match.empty()){
        auto rule_to_apply = matching_rule(matched_shapes.match, false, shape_map);
        if (rule_to_apply != nullptr){
            return make_pair(matched_shapes, rule_to_apply);
        }
    }
//    printf("[TIME] Didn't find any rule for matching\n");
    return pair<PartitionShapeGroup, Rule*>(PartitionShapeGroup(), nullptr);
}

pair<PartitionShapeGroup, Rule*> matching_anim_shape(Grammar* g, const ShapeGroup& active_shapes, const map<Shape*, TimeManager::NodeTimeLine*>& shape_map){
    //matching of the shapes
    auto matched_shapes = matching_shapes(active_shapes, true, shape_map);
    //matching of the rule
    if (not matched_shapes.match.empty()){
        auto rule_to_apply = matching_rule(matched_shapes.match, true, shape_map);
        if (rule_to_apply != nullptr){
            return make_pair(matched_shapes, rule_to_apply);
        }
    }
//    printf("[SPACE] Didn't find any rule for matching\n");
    return pair<PartitionShapeGroup, Rule*>(PartitionShapeGroup(), nullptr);
}


bool tag_in_rule(int tag, const rule_tags& tags){
    for (auto i = 0; i < TAG_SIZE; i++){
        if (tag == tags[i]) return true;
    }
    return false;
}

Rule* tangle_match_rule(Grammar* grammar, int tag, const vector<int>& temporal_tags){
    switch (ACTIVE_GRAMMAR) {
        case tangle_grammar:
        {
            auto matches = vector<int>();
            auto grammar = get_grammar(grammar_filename);
            auto rules = get_rules(grammar);
            for(auto i = 0; i < (int)rules.size(); i++){
                if (tag_in_rule(tag, rules[i]->matching_tags))
                    matches.push_back(i);
            }
            if(matches.empty()) return nullptr;
            return rules[matches[(int)(ym_rng_nextf(&grammar->rn) * matches.size())]];
        }
        case animation_grammar:
        {
            auto matches = vector<int>();
            auto grammar = get_grammar(grammar_filename);
            auto rules = get_rules(grammar);
            for(auto i = 0; i < (int)rules.size(); i++){
                if (temporal_tags.empty() || rules[i]->op.init_value == tag_to_mapping(grammar, "")){
                    if (tag_in_rule(tag, rules[i]->matching_tags))
                        matches.push_back(i);
                }
                else{
                    if (tag_in_rule(tag, rules[i]->matching_tags)
                        and (std::find(temporal_tags.begin(), temporal_tags.end(), rules[i]->op.init_value) != temporal_tags.end())){
                        matches.clear();
                        matches.push_back(i);
                        break;
                    }
                }
            }
            if(matches.empty()) return nullptr;
            if (tag == 1)
                printf(" ");
            auto f_idx = ym_rng_nextf(&(grammar->rn)) * (float)matches.size();
            auto r_idx = (int)(f_idx);
            return rules[matches[r_idx]];
        }
        default:
            break;
    }
    return nullptr;
}

PartitionShapeGroup matching_shapes(const ShapeGroup& active_shapes, bool anim_shape, const map<Shape*, TimeManager::NodeTimeLine*>& shape_map){
    auto res = PartitionShapeGroup();
    auto grammar = get_grammar(grammar_filename);
    switch (ACTIVE_GRAMMAR) {
        case tangle_grammar:
        {
            auto rule = (Rule*)nullptr;
            auto start = (TangleShape*)nullptr;
            for(auto&& shape : active_shapes) {
                rule = tangle_match_rule(grammar, ((TangleShape*)shape)->tag);
                start = ((TangleShape*)shape);
                if(rule) break;
            }
            if(not rule) return res;
            for(auto shape : active_shapes) {
                if(((TangleShape*)shape)->gid == start->gid) res.match.push_back(shape);
                else res.remainder.push_back(shape);
            }
            break;
        }
        case animation_grammar:
        {
            
            // [X] TODO: ADD CHECK FOR TEMPORAL TAG AS WELL AS SPATIAL TAGS
            //       - A RULE IS MATCHED IF IT CAN BE APPLIED ON AVAILABLE 2D SHAPES
            //          **AS WELL AS** ON AVAILABLE TAGGED SLICES
            
            if (!anim_shape){
                auto rule = (Rule*)nullptr;
                auto start = (TimeSliceShape*)nullptr;
                for(auto&& shape : active_shapes) {
                    auto temp = (TimeSliceShape*)shape;
                    rule = tangle_match_rule(grammar, temp->slice->ts_tag, make_vector(shape_map.at(temp)->node->content->shapes, [&](AnimatedShape* shape){return shape->tag;}));
                    start = ((TimeSliceShape*)shape);
                    if(rule) break;
                }
                if(not rule) return res;
                auto start_node = shape_map.at(start);
                auto shape_tags = make_set(make_vector(start_node->node->content->shapes, [&](AnimatedShape* shape){return shape->tag;}));
                auto g = get_grammar(grammar_filename);
                auto inv_tag = tag_to_mapping(g, "inv_" + mapping_to_tag(g, start->slice->ts_tag));
                
                for(auto shape : active_shapes) {
                    auto temp_ts = (TimeSliceShape*)shape;
                    auto temp_node = shape_map.at((TimeSliceShape*)shape);
                    auto temp_tags = make_set(make_vector(temp_node->node->content->shapes, [&](AnimatedShape* shape){return shape->tag;}));
                    std::vector<int> intersection;
                    set_intersection(shape_tags.begin(),shape_tags.end(),temp_tags.begin(),temp_tags.end(), std::back_inserter(intersection));
                    
                    if( (temp_ts->slice->ts_tag == start->slice->ts_tag) && (!intersection.empty()) )
                        res.match.push_back(shape);
                    else if ((temp_ts->slice->ts_tag == inv_tag) && (!intersection.empty())) {
                        res.match.push_back(shape);
                    }
                    else res.remainder.push_back(shape);
                }
            }
            else{
                auto rule = (Rule*)nullptr;
                auto start = (AnimatedShape*)nullptr;
                auto start_node = (TimeManager::NodeTimeLine*)nullptr;
                for(auto&& shape : active_shapes) {
                    auto temp = (AnimatedShape*)shape;
                    auto ntl = shape_map.at(temp);
                    rule = tangle_match_rule(grammar, temp->tag, make_vector(ntl->slices, [&](TimeManager::TimeSlice* slice){return slice->ts_tag;}));
                    start = ((AnimatedShape*)shape);
                    start_node = ntl;
                    if(rule) break;
                }
                if(not rule) return res;
                
                auto g = get_grammar(grammar_filename);
                for(auto shape : active_shapes) {
                    if(((AnimatedShape*)shape)->tag == start->tag) {
                        auto ntl = shape_map.at((AnimatedShape*)shape);
                        auto ntl_tags = make_vector(ntl->slices, [&](TimeManager::TimeSlice* slice){return slice->ts_tag;});
                        
                        if (std::find(ntl_tags.begin(), ntl_tags.end(), rule->op.init_value) != ntl_tags.end()) {
                            res.match.push_back(shape);
                        }
                        else if (std::find(ntl_tags.begin(), ntl_tags.end(), invert_tag(g, rule->op.init_value)) != ntl_tags.end()) {
                            res.match.push_back(shape);
                        }
                        else { res.remainder.push_back(shape); }
                    }
                    else {
                        res.remainder.push_back(shape);
                    }
                }
            }
            break;
        }
        default:
            printf("[matching_shapes] ERROR: Shouldn't have gotten here! Invalid grammar_type \n");
            break;
    }
    return res;
}

Rule* matching_rule(const ShapeGroup& matched, bool anim_shape, const map<Shape*, TimeManager::NodeTimeLine*>& shape_map) {
    auto grammar = get_grammar(grammar_filename);
    switch (ACTIVE_GRAMMAR) {
        case tangle_grammar:
        {
            auto shape = matched[0];
            auto rule = tangle_match_rule(grammar, ((TangleShape*)shape)->tag);
            return rule;
        }
        case animation_grammar:
        {
            auto shape = matched[0];
            auto rule = new Rule();
            
            if (!anim_shape) {
                rule = tangle_match_rule(grammar, ((TimeSliceShape*)shape)->slice->ts_tag, make_vector(shape_map.at(shape)->node->content->shapes, [&](AnimatedShape* shape){return shape->tag;}));
            }
            else {
                auto ntl = shape_map.at((AnimatedShape*)shape);
                auto ntl_tags = make_vector(ntl->slices, [&](TimeManager::TimeSlice* slice){return slice->ts_tag;});
                rule = tangle_match_rule(grammar, ((AnimatedShape*)shape)->tag, ntl_tags);
            }
            return rule;
        }
        default:
            printf("[matching_rule] ERROR: Shouldn't have gotten here! Invalid grammar_type \n");
            break;
    }
    return nullptr;
}