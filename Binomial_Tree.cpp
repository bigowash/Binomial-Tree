#include <iostream>
#include <vector>
#include <string>
  
// you can include other headers 
// you need for your code
  
// you can use only headers from the C++ standard library
  
// you can use any headers from the C++ standard library
// except for the algorithm header
  
// do not use "using namespace std;"

// do not alter this structured data type definition
struct BNode{
    std::string val;
    // this will contain
    // "xn" (e.g. x3 or x1 etc) in non-leaf nodes
    // "0" or "1" in leaf nodes
  
    BNode* left;
    // this will conventionally represent the 0 branch
    BNode* right;
    // this will conventionally represent the 1 branch
  
    // (as usual leaf nodes will have both left and right pointing to NULL)
};
  
// you can define here other functions to use in the code below

BNode* build_tree(int size, int x) {
    BNode* b = new BNode;

    if (size == 0) {
        b->val = "0";
        b->left = NULL;
        b->right = NULL;
    }
    else {
        b->val = "x" + std::to_string(x);
        b->left = build_tree(size - 1, x + 1);
        b->right = build_tree(size - 1, x + 1);
    }

    return b;
}

void value(BNode* bt, std::string v) {
    if (v == "") {
        bt->val = "1";
    }
    else if (v.substr(0, 1) == "1") {
        value(bt->right, v.substr(1, v.size() - 1));
    }
    else {
        value(bt->left, v.substr(1, v.size() - 1));
    }
}

bool in_vector(std::string first, std::vector<std::string> fvalues){
  if (fvalues.size() < 1){
    return false;
  }
  else if (fvalues.front() == first){
    return true;
  }
  fvalues.erase(fvalues.begin()); // removes the first element
  return in_vector(first, fvalues);
}

std::vector<std::string> compare_strings(std::vector<std::string> fvalues){
  
  std::vector<std::string> returnedchanges;

  for (int i = 0; i < fvalues.size(); i++){
    std::string first = fvalues[0];
    fvalues.erase(fvalues.begin()); // removes the first element
    if (in_vector(first, fvalues)){
      returnedchanges.push_back(first);
    }
  }

  return returnedchanges;
}

void implement_changes(BNode* bt, std::string change){
  if (change == "") {
    bt->val = bt->left->val; 
    bt->left = NULL;
    bt->right = NULL;
  }
  else if (change.substr(0, 1) == "1") {
      implement_changes(bt->right, change.substr(1, change.size() - 1));
  }
  else {
      implement_changes(bt->left, change.substr(1, change.size() - 1));
  }
}

BNode* refine_tree(BNode* bt, std::vector<std::string> fvalues){
  for (int i = 0; i < fvalues.size(); i++){
    // removes the last element from each fvalues element
    if (!fvalues[i].empty()) fvalues[i].pop_back();
  }

  std::vector<std::string> changes = compare_strings(fvalues);

  if (changes.size() != 0){
    for (int i = 0; i < changes.size(); i++){
      implement_changes(bt, changes[i]);
    }
  }
  
  return bt;
}

bool refine_tree_better(BNode* &bt){
  // is left a leaf
  if (bt->left->val == "0" || bt->left->val == "1"){
    // is right a leaf
    if (bt->right->val == "0" || bt->right->val == "1"){
      // are leaves the same
      if (bt->right->val == bt->left->val){
        bt->val = bt->left->val; 
        bt->left = NULL;
        bt->right = NULL;
        return true;
      }
      else {
        return false;
      }
    }
    else { // left is leaf but not right
      // goes down the right
      return refine_tree_better(bt->right);
    }
  }
  else {
    // goes down the left
    return refine_tree_better(bt->left);
  }
}

std::string get_string(BNode* bt){
  if (bt->val == "0" || bt->val == "1"){
    return bt->val;
  }
  else {
    std::string returnedstring;
    returnedstring.append(bt->val);
    returnedstring.append(get_string(bt->left));
    returnedstring.append(get_string(bt->right));
    return returnedstring;
  }
}

BNode* rebuild_tree(BNode* bt, std::string blueprint){
  
  if (blueprint.size() == 1){
    bt->val = blueprint[0];
    bt->left = NULL;
    bt->right = NULL;
  }
  else{
    bt->val = blueprint.substr(0,2);
    blueprint = blueprint.substr(2, blueprint.size()-2);
    
    // this node connects to leaves
    if (blueprint.size() == 2){
      // ending leaves
      bt->left->val = blueprint[0];
      bt->left->left = NULL;
      bt->left->right = NULL;

      bt->right->val = blueprint[1];
      bt->right->left = NULL;
      bt->right->right = NULL;
    }
    else{
      bt->left = rebuild_tree(bt->left, blueprint.substr(0, blueprint.size()/2));
      bt->right = rebuild_tree(bt->right, blueprint.substr(blueprint.size()/2));
    }
  }
  return bt;
}

void perfect_tree(BNode* &bt){

  if (bt->val[0] == 'x'){
    
    std::string tempstring = get_string(bt->left);

    if (tempstring == get_string(bt->right)){
      bt = rebuild_tree(bt, tempstring);
      perfect_tree(bt); // to be thorough
    }
    
    else {
      // perfect the left branch
      perfect_tree(bt->left);
      // perfect the right branch
      perfect_tree(bt->right);
    }
  }
}

// you can also define here other 
// structured data types or classes 
// (including member data and member functions) 
// to use in the code below

// do not alter the following line that begins the function build_bt
BNode* build_bt(const std::vector<std::string>& fvalues){
    // complete this function
    BNode* bt;
    
    bt = build_tree(fvalues[0].size(), 1);
    
    for (int i = 0; i < fvalues.size(); i++) {
        value(bt, fvalues[i]);
    }

    // bt = refine_tree(bt, fvalues);
    // while (refine_tree_better(bt)); // this does not work because if the left most node does not change, then the program is done
    perfect_tree(bt);

    return bt;
}
  
// do not alter the following function
// this function converts e.g. std::string "x3" to int 2
int label_to_idx(const std::string& label){
  
    std::string out;
  
    for(int i = 1; i < label.size(); i++){
        out.push_back(label[i]);
    }
  
    return std::stoi(out) - 1;
}
  
// do not alter the following function
std::string eval_bt(BNode* bt, const std::string& input){
  
    if( (bt->left == NULL) && (bt->right == NULL) ){
        return bt->val;
    }
    else{
        int idx = label_to_idx(bt->val);
        std::string input_idx;
        input_idx.push_back(input[idx]);
  
        if(input_idx == "0"){
            return eval_bt(bt->left, input); 
        }
        else{
            return eval_bt(bt->right, input); 
        }
    }
}
  
// do not alter the following function
int n_nodes_bt(BNode* t){
    if(t == NULL){
        return 0;
    }
    else{
        return 1 + n_nodes_bt(t->left) + n_nodes_bt(t->right);
    }
}
  
class BoolTree{
  public:
      BoolTree(const std::vector<std::string>& fvalues){
          t = build_bt(fvalues);
      }

      std::string eval(const std::string& s){
          return eval_bt(t, s);
      }
    
      int n_nodes(){
          return n_nodes_bt(t);
      }

      ~BoolTree(){
          // complete this function 
          // (do not alter in any other way class BoolTree)
    
          // keep in mind that you can include in this function 
          // calls to functions defined outside class BoolTree
          // (as done in the member functions above)
          // and that you can define other functions
          // above and outside this class

          deallocate_tree(t);
    
      }

      
    
  private:
      BNode* t;
};
  
// the main provided below must work correctly
// with your implementation for the code above
// however you can change it as you wish for your own testing 
// and your changes won't be considered for the assessment
// (in your submission you can also have an empty main or no main at all)
  
int main(){
  
    std::vector<std::string> fv;
    std::string row;
  
    row = "11";
    fv.push_back(row);
  
    BoolTree ft1(fv);
  
    fv.clear();
  
    row = "010";
    fv.push_back(row);
    row = "011";
    fv.push_back(row);
    row = "110";
    fv.push_back(row);
    row = "111";
    fv.push_back(row);
  
    BoolTree ft2(fv);
  
    fv.clear();

    row = "00000";
    fv.push_back(row);
    row = "00010";
    fv.push_back(row);
    row = "00100";
    fv.push_back(row);
    row = "00110";
    fv.push_back(row);
    row = "01000";
    fv.push_back(row);
    row = "01010";
    fv.push_back(row);
    row = "01100";
    fv.push_back(row);
    row = "01110";
    fv.push_back(row);
    row = "10000";
    fv.push_back(row);
    row = "10010";
    fv.push_back(row);
    row = "10100";
    fv.push_back(row);
    row = "10110";
    fv.push_back(row);
    row = "11000";
    fv.push_back(row);
    row = "11010";
    fv.push_back(row);
    row = "11100";
    fv.push_back(row);
    
    BoolTree ft3(fv);

    std::cout << ft1.n_nodes() << std::endl;
    // we expect this to print 5
  
    std::cout << ft2.n_nodes() << std::endl;
    // if the algorithm is such that it builds the smallest possible corresponding tree
    // for the boolean function we are considering
    // then this will print 3 (see tree diagram in the example above)
  
    std::cout << ft3.n_nodes() << std::endl;

    std::cout << ft1.eval("01") << std::endl;
    // this should print "0" 
  
    std::cout << ft1.eval("11") << std::endl;
    // this should print "1"
  
    std::cout << ft2.eval("001") << std::endl;
    // this should print "0"
  
    std::cout << ft2.eval("110") << std::endl;
    // this should print "1"

}