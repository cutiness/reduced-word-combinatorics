/*
The GPLv3 License (GPLv3)

Copyright (c) 2022 cutiness

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
//#include <chrono>

using namespace std;

#define MAX_COLUMN 10

vector<vector<int>> tower_decomposition(vector<int> word){
  vector<int> temp;
  vector<vector<int>> word_decomposed;

  temp.push_back(word[0]); // first element is always the starting point of the first tower
  for(int i = 1; i < word.size(); i++){
    if(word[i] == word[i-1] + 1) temp.push_back(word[i]);
    
    else{
      word_decomposed.push_back(temp); //if the condition is not satisfied we end the tower
      temp.clear();
      temp.push_back(word[i]);
    }
  }
  word_decomposed.push_back(temp); // this adds the last instance of temp to the decompostion
  return word_decomposed;
}

// this functions updates the tower decomposition of a given word, if new elements are added
// or some elements are swapped, there is a chance that new towers are formed, function calls itself again
// at the first time that it finds an issue
// note : if there is nothing wrong, the given decomposition will remain unchanged
vector<vector<int>> update_decomposition(vector<vector<int>> word_decomposed){
  for(int i = 0; i < word_decomposed.size() - 1; i++){
    if(word_decomposed[i].back() + 1 == word_decomposed[i+1].front()){
      // concatenating tower 'i' and 'i+1'
      for(int j = 0; j < word_decomposed[i+1].size(); j++){
        word_decomposed[i].push_back(word_decomposed[i+1][j]);
      }
      word_decomposed.erase(word_decomposed.begin() + i + 1); //deletes the 'i+1' tower after concatenation
      word_decomposed = update_decomposition(word_decomposed); //function calls itself in case there are other parts with the smae issue
      break;
    }
  }
  return word_decomposed;
}

// this function just prints out values inside a word, without spaces
void print_word(vector<int> word){
  for(int i = 0; i < word.size(); i++){
    cout << word[i];
  }
}

//does the some thing as print_word , but for tower_decompositions
void print_decomposition(vector<vector<int>> word_decomposed, int num = 5){
  for(int i = 0; i < word_decomposed.size(); i++){
    for(int j = 0; j < word_decomposed[i].size(); j++){
      cout << word_decomposed[i][j];
    }
    cout << (((i + 1) % MAX_COLUMN == 0) ? "\n" : " ");
  }
  if(word_decomposed.size() % MAX_COLUMN != 0) cout << "\n";
}

//prints out the password set which is a 3d vector
void print_passwords(vector<vector<vector<int>>> passwd){
  for(int i = 0; i < passwd.size(); i++){
    print_decomposition(passwd[i]);
  }
}

//this function removes duplicate element from a 3d vector, used in password functions
//it has no meaning by its own
vector<vector<vector<int>>> remove_duplicates3d(vector<vector<vector<int>>> dvec){
  vector<vector<vector<int>>> temp = dvec;
  for(int i = 0; i < dvec.size(); i++){
    int cnt = count(temp.begin(), temp.end(), dvec[i]);
    if(cnt > 1){
      auto fnd = find(temp.begin(), temp.end(), dvec[i]);
      temp.erase(fnd);
    }
  }
  return temp;
}

//this function removes duplicate element from a 2d vector
//it has no meaning by its own
vector<vector<int>> remove_duplicates2d(vector<vector<int>> dvec){
  vector<vector<int>> temp = dvec;
  for(int i = 0; i < dvec.size(); i++){
    int cnt = count(temp.begin(), temp.end(), dvec[i]);
    if(cnt > 1){
      auto fnd = find(temp.begin(), temp.end(), dvec[i]);
      temp.erase(fnd);
    }
  }
  return temp;
}

// this function swaps places of the elements located at index1 and index2 in "word"
vector<int> swap_place(vector<int> word, int index1, int index2){
  vector<int> new_word = word;
  new_word.insert(new_word.begin() + index1, word[index2]); // places index2 to the place of index1
  new_word.erase(new_word.begin() + index1 + 1); // removes the old element
  new_word.insert(new_word.begin() + index2, word[index1]); // places index1 to the place of index2
  new_word.erase(new_word.begin() + index2 + 1); // removes the old element
  return new_word;
}

bool check_relation1(vector<int> word1, vector<int> word2){
  vector<int> temp = word1;
  for(int i = 0; i < word1.size() - 1; i++){
    if(word1[i] + 2 <= word1[i+1]){
      temp = swap_place(temp, i, i+1);
      if(temp == word2) return true; // if swapped version of word1 is equal to word2 we are done
      else temp = word1; // otherwise we set temp back to its original form
    }
  }
  return false; //if we did not return true inside the loop, then it should be false
}

// this definition here might not be totally correct, gotta ask
bool check_lexiographic(vector<int> word1, vector<int> word2){
  if(word1.size() < word2.size()) return true; // if word1 has less digits, it is clearly smaller
  else if(word1.size() > word2.size()) return false; // if not word1 is clearly bigger
  // if nothing is returned up to this point, the following is executed
  else if(word1 == word2) return true; // if they are equal, return true
  for(int i = 0; i < word1.size(); i++){
    if(word2[i] > word1[i]) return true;
  }
  // if all of the above did not return true, then it is false
  return false;
}

bool check_relation2(vector<int> word1, vector<int> word2){
  if(!check_lexiographic(word1, word2)) return false; // relation2 implies lexiographic
  auto word1_decomposed = tower_decomposition(word1); 
  auto word2_decomposed = tower_decomposition(word2);
  vector<int> b1; vector<int> b2; auto temp = word1_decomposed;

  for(int i = 0; i < word1_decomposed.size() - 1; i++){
    // termination conditions may need to be adjusted, check later**
    if(word1_decomposed[i].front() > word1_decomposed[i+1].front() || 
       word1_decomposed[i+1].front() > word1_decomposed[i+1].back()  || //dummy condition (??)
       word1_decomposed[i+1].back() >= word1_decomposed[i].back() ) continue;
    // if the input reached here, it means 'i' is a worthy candidate
    b1.clear(); b2.clear(); temp = word1_decomposed;
    // if the tower has size 1 there is only one way to choose (b2 empty)
    if(word1_decomposed[i+1].size() == 1){
      b1.push_back(word1_decomposed[i+1].front() + 1); // this creates b1 tilda (elements + 1)
      temp.insert(temp.begin() + i, b1); //b1 is placed at the position of 'i' th tower
      temp.erase(temp.begin() + i + 2); // removing the old 'i+1' th tower
      temp = update_decomposition(temp); //updating temp in case new towers are formed
      if(temp == word2_decomposed) return true;
    }
    // if tower has size more than 1 , there are multiple ways to choose b1 and b2
    else{
      for(int j = 0; j < word1_decomposed[i+1].size(); j++){
        b1.clear(); b2.clear(); temp = word1_decomposed; // old values from older iterations are cleaned here
        for(int k = 0; k <= j; k++){
          b1.push_back(word1_decomposed[i+1][k] + 1); //b1 tilda
        }
        for(int k = word1_decomposed[i+1].size() - 1; k > j; k--){
          // in case j = last-index , then b2 will be empty, which is a legal possibility
          b2.insert(b2.begin(), word1_decomposed[i+1][k]);
        }
        temp.insert(temp.begin() + i, b1);
        temp.erase(temp.begin() + i + 2); //removing the old 'i+1' th tower
        //b2 is put in the place of the old 'i+1' th tower , if it is nonempty
        if(b2.size() != 0) temp.insert(temp.begin() + i + 2, b2);
        temp = update_decomposition(temp); //updating temp in case new towers are formed
        if(temp == word2_decomposed) return true;
      }
    }  
  }
  // if 'true' is not returned up to this point, then such an 'i' satisfying all conditions do not exist
  return false;
}

//this algorithm uses the relation1 to create a natural basic word from a given reduced word
vector<vector<int>>selection_sort(vector<vector<int>> word_decomposed, vector<int> unwanted_indexes={-1}){
  //the extreme case is when the word_decomposed has size 1 , we handle it outside the function
  //terminating condition , if fin(b_s) > in(b_s+1)
  for(int i = 0; i < word_decomposed.size() - 1; i++){
    if(word_decomposed[i].back() <= word_decomposed[i+1].front()) break;
    //if we did not exit the loop up to last 'i' value, then word_decomposed is indeed
    //a natural word, so we just return it
    if(i == word_decomposed.size() - 2) return word_decomposed;
  }

  auto temp = word_decomposed;
  vector<vector<int>> result;  
  vector<int> initial_elements;
  for(int i = 1; i < unwanted_indexes.size(); i++) temp.erase(temp.begin() + unwanted_indexes[i]);
  for(int i = 0; i < temp.size() - 1; i++) initial_elements.push_back(temp[i].front()); // we simply omit the last tower
  int b_s, b_s_index; // smallest element and the index of the right most tower starting with b_s
  b_s = *min_element(initial_elements.begin(), initial_elements.end());
  
  for(int i = word_decomposed.size() - 2; i >= 0; i--){ //we do not check the last tower, even if it starts with the min element, we simply do not care
    if(word_decomposed[i].front() == b_s && find(unwanted_indexes.begin(), unwanted_indexes.end(), i) == unwanted_indexes.end()){
      b_s_index = i; break;
    }
  }
  
  if(word_decomposed[b_s_index].back() < word_decomposed[b_s_index+1].front()){
    //swapping places of b_s and b_(s+1)
    word_decomposed.insert(word_decomposed.begin() + b_s_index, word_decomposed[b_s_index+1]);
    word_decomposed.erase(word_decomposed.begin() + b_s_index + 2); // removes the extra element in the old place
    int old_size = word_decomposed.size();
    word_decomposed = update_decomposition(word_decomposed); //we update decomposition in case new towers are formed
    int new_size = word_decomposed.size();
    // if no new towers are formed, we may call the function again with the same unwanted_indexes
    // otherwise the function is called with the default value of unwanted_indexes , this is just for
    // optimization purposes
    if(new_size == old_size) result = selection_sort(word_decomposed, unwanted_indexes);
    else result = selection_sort(word_decomposed);
  }
  //if conditions are not satisfied , we no longer want to check this index
  else{
    unwanted_indexes.push_back(b_s_index);
    result = selection_sort(word_decomposed, unwanted_indexes);
  }
  return result;
}

//this algorithm uses relation2 obtain the unique natural word out of a given natural basic word
vector<vector<int>>insertion_sort(vector<vector<int>> word_decomposed){
  //the extreme case is when the word_decomposed has size 1 , we handle it outside the function
  //terminating condition
  for(int i = 0; i < word_decomposed.size() - 1; i++){
    // if initials of the towers create a strictly decreasing sequnce we just return it directly
    if(word_decomposed[i].front() <= word_decomposed[i+1].front()) break;
    if(i == word_decomposed.size() - 2) return word_decomposed;
  }
  
  vector<vector<int>> result;
  int i_max; // greatest index with in(b_i) <= in(b_i+1)
  for(int i = word_decomposed.size() - 1; i >= 1; i--){
    if(word_decomposed[i-1].front() <= word_decomposed[i].front()){
      i_max = i-1; break;
    }
  }
  
  vector<int> temp = {};
  for(int i = 0; i < word_decomposed[i_max+1].size(); i++) temp.push_back(word_decomposed[i_max+1][i] + 1); //creates b_i+1 tilda
  word_decomposed.insert(word_decomposed.begin() + i_max, temp);
  word_decomposed.erase(word_decomposed.begin() + i_max + 2);

  // there is only one way to go in these cases, so we may handle it here
  if(i_max == 0) result = insertion_sort(word_decomposed);
  // this compares b_i-1 with b_i+1 tilda which is at the 'i' th index after swapping the places
  else if(word_decomposed[i_max-1].back() > word_decomposed[i_max].front()) result = insertion_sort(word_decomposed);
  else if(word_decomposed[i_max-1].back() + 1 == word_decomposed[i_max].front()){
    // if this is the case, a new tower will be formed
    word_decomposed = update_decomposition(word_decomposed);
    result = insertion_sort(word_decomposed);
  }
  // if we have fin(b_i-1) + 1 < in(b_i+1)^tilda then we push b_i+1 tilda to left enough times so that
  // the resulting decomposition becomes a natural basic word
  else{
    for(int i = i_max; i >= 1; i--){
      word_decomposed.insert(word_decomposed.begin() + i - 1, word_decomposed[i]);
      word_decomposed.erase(word_decomposed.begin() + i + 1); //deleting the old element after swapping
      // if what we obtained is a natural basic word, then selection sort will just return it back, in that case we exit the loop 
      if(selection_sort(word_decomposed) == word_decomposed) break;
    }
    result = insertion_sort(word_decomposed);
  }
  return result;
}

// given a reduced word w, password(b,a) returns a set of word in their decomposed form
// using the track sequnce of b through w , it is subject to some conditions that i will not mention here
vector<vector<vector<int>>> passwords(int b, vector<vector<int>> word_decomposed){
  // after adding b, to the beginning of w, the result should be a reduced word
  // may need to check that later, for now I assume the given b creates a reduced word
  vector<vector<vector<int>>> result;
  vector<vector<int>> temp;

  vector<int> track_seq = {b};
  
  //creating the track sequence
  for(int i = 0; i < word_decomposed.size(); i++){
    if(word_decomposed[i].front() < track_seq[i] && track_seq[i] <= word_decomposed[i].back()){
      track_seq.push_back(track_seq[i] - 1);
    }
    else if(track_seq[i] <= word_decomposed[i].front() - 2 || track_seq[i] >= word_decomposed[i].back() + 2){
      track_seq.push_back(track_seq[i]);
    }
    else break;
  }
  //creating the password set
  for(int i = 0; i < track_seq.size(); i++){
    temp = word_decomposed;
    vector<int> l1_tower = {track_seq[i]};
    temp.insert(temp.begin() + i, l1_tower);
    temp = update_decomposition(temp);
    result.push_back(temp);
  } 
  remove_duplicates3d(result);
  return result;
}

//does exactly what passwords function does, just on an entire word, rather than
//just one integer
vector<vector<vector<int>>> passwords_union(vector<vector<int>> word1_decomposed, vector<vector<int>> word2_decomposed){
  //
  vector<vector<vector<int>>> result = {word2_decomposed}; vector<vector<vector<int>>> temp;
  
  for(int i = 0; i < word1_decomposed.size(); i++){
    for(int j = 0; j < word1_decomposed[i].size(); j++){
      //this part creates all possible combinations of password(b, a) and stores is inside 'temp'
      for(int k = 0; k < result.size(); k++){
        auto temp2 = passwords(word1_decomposed[i][j], result[k]);
        for(int l = 0; l < temp2.size(); l++) temp.push_back(temp2[l]);
      }
      //to use the new password set in the next iteration we pass everything to the 'result' variable
      result = temp; temp.clear();
    }
  }
  result = remove_duplicates3d(result);
  return result;
}

//given a word in its decomposed form, this functions returns the set of its basic words
//using passwords_union function above
vector<vector<vector<int>>> basic_words(vector<vector<int>> word_decomposed){
  vector<vector<vector<int>>> result = {{word_decomposed[0]}}; vector<vector<vector<int>>> temp;
  for(int i = 0; i < word_decomposed.size() - 1; i++){
    for(int j = 0; j < result.size(); j++){
      auto temp2 = passwords_union(result[j], {word_decomposed[i+1]});
      for(int l = 0; l < temp2.size(); l++) temp.push_back(temp2[l]);
    }
    result = temp; temp.clear();
  }
  result = remove_duplicates3d(result);
  return result;
}

//written to be used in the definition of restricted_shuffle , has no meaning on its own
vector<vector<int>> restricted_shuffle_base(vector<int> word1, vector<int> word2){
  //terminating condition
  if(word2.size() == 0) return {{}}; //returns an empty 2d vector

  vector<vector<int>> result; vector<int> concatenated_words = word1;
  for(int l = 0; l < word2.size(); l++) concatenated_words.push_back(word2[l]);
  result.push_back(concatenated_words);

  for(int i = word1.size() - 1; i >= 0; i--){
    bool possible = true;
    if(word2[0] == word1[i]) possible = false;
    else if(word2[0] == word1[i] - 1 || word2[0] == word1[i] + 1) possible = false;
    // if 'possible' stays true, we investigate further
    if(possible){
      auto temp = concatenated_words;
      temp.insert(temp.begin() + i, word2[0]); temp.erase(temp.begin() + word1.size() + 1);
      // as 'temp' is a mew combination we add it to 'result' as well
      result.push_back(temp);
      //initializing the new variables to call the function again
      vector<int> new_word1; vector<int> new_word2;
      for(auto itr = word1.begin() + i; itr != word1.end(); itr++) new_word1.push_back(*itr);
      for(auto itr = word2.begin() + 1; itr != word2.end(); itr++) new_word2.push_back(*itr);
      auto sub_result = restricted_shuffle_base(new_word1, new_word2);
      //we add the cut out part again to every element in the sub_result , so it makes sense
      for(int m = 1; m < sub_result.size() ; m++){ //the first element will create a copy, so we omit it and start from index 1
        for(int k = i; k >= 0; k--) sub_result[m].insert(sub_result[m].begin(), temp[k]);
      }
      //now we add it at the end of 'result'
      for(int m = 1; m < sub_result.size() ; m++) result.push_back(sub_result[m]);
    }
    else break;
  }
  return result;
}

//this is the main restricted_shuffle functions, given a word in its decomposed form this
//returns all possible shuffle combinations
vector<vector<int>> restricted_shuffle(vector<vector<int>> word_decomposed){
  vector<vector<int>> result = {word_decomposed[0]}; vector<vector<int>> temp;

  for(int i = 0; i < word_decomposed.size() - 1; i++){
    for(int j = 0; j < result.size(); j++){
      auto temp2 = restricted_shuffle_base(result[j], word_decomposed[i+1]);
      for(int l = 0; l < temp2.size(); l++) temp.push_back(temp2[l]);
    }
  result = temp; temp.clear();
  }
  //result = remove_duplicates2d(result);
  return result;
}

//this is the most precious function of this entire program, the result of everything that was defined above
//it returns a complete list of reduced words of a given permutation (given with its tower decomposition)
vector<vector<int>> reduced_words(vector<vector<int>> word_decomposed){
  vector<vector<int>> word_natural;
  //the extreme case
  if(word_decomposed.size() == 1) word_natural = word_decomposed; 

  //this is the unique natural word of the given reduced word
  else word_natural = insertion_sort(selection_sort(word_decomposed));

  vector<vector<vector<int>>> word_basic = basic_words(word_natural); // the set of basic words of the given word
  vector<vector<int>> result; vector<vector<int>> temp;
  //the union of restricted_shuffles of every element inside the word_basic set
  for(int i = 0; i < word_basic.size(); i++){
    temp = restricted_shuffle(word_basic[i]);
    for(int l = 0; l < temp.size(); l++) result.push_back(temp[l]);
  }
  result = remove_duplicates2d(result);
  return result;
}

//remaning part is just for the driver-code, has nothing to do with the algorithm
vector<vector<int>> standart_prompt(void){
  vector<vector<int>> result;
  char temp_char = -1;
  vector<int> word1; vector<int> word2;
  printf("\n%s\n%s", "  Please enter two words, without spaces: ",
                       "  Word1: ");
  temp_char = getc(stdin);
  while(temp_char != '\n'){
    int temp = temp_char - 48;
    //this part checks if the input is a number
    if(temp < 0 || temp > 9){
      cout << "  The input should contain only numbers!\n";
      exit(0);
    }
    else{ 
      word1.push_back(temp_char - 48);
      temp_char = getc(stdin);
    }
  }
  printf("%s", "  Word2: ");
  temp_char = getc(stdin);
  while(temp_char != '\n'){
    int temp = temp_char - 48;
    //this part checks if the input is a number
    if(temp < 0 || temp > 9){
      cout << "  The input should contain only numbers!\n";
      exit(0);
    }
    else{ 
      word2.push_back(temp_char - 48);
      temp_char = getc(stdin);
    }
  }
  result.push_back(word1); result.push_back(word2);
  return result;
}

vector<int> word_prompt(void){
  char temp_char = -1;
  vector<int> word1;
  printf("\n%s\n%s", "  Please enter a word, without spaces: ",
                       "  Word: ");
  temp_char = getc(stdin);
  while(temp_char != '\n'){
    int temp = temp_char - 48;
    //this part checks if the input is a number
    if(temp < 0 || temp > 9){
      cout << "  The input should contain only numbers!\n";
      exit(0);
    }
    else{ 
      word1.push_back(temp_char - 48);
      temp_char = getc(stdin);
    }
  }
  return word1;
}

int main(void){
  
  //intro ascii-art
  printf("\n%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
  "                                                                                                              MNOdkNM                                  \n",                                                                                              
  "                                                                                                            WXkc'.'ckXW                                \n",
  "                                                                                                           Mkc'.'''.':kM                               \n",
  "                                                                                                         Nkc'.''''''''':kM                             \n",
  "                                                                                                       Nkc'.'''''.'''''.':kM                           \n",
  "                                                                                                     Nkc'.''''',;;;;::;;,'':kM                         \n",
  "       ___              _     _              _              _        _                             Xkc''''',;:lloooooooollc;,:kW                       \n",
  "      / __| ___  _ __  | |__ (_) _ _   __ _ | |_  ___  _ _ (_) __ _ | |                          Nkc''''.';looooooooooooooool;,:kN                     \n",
  "     | (__ / _ \\| '  \\ |  _ \\| || ' \\ / _` ||  _|/ _ \\| '_|| |/ _` || |                        Nkc'''.'',:ooooooooooooooooooooc,':kK              \n",
  "      \\___|\\___/|_|_|_||____/|_||_||_|\\__/_| \\__|\\___/|_|  |_|\\__/_||_|                      Nkc'.''.'.':loooooooooooooooooooooc'.':kK           \n",
  "                                                                                           Xkc'.''.'.'',cooooooooooooooooooooool;'.'':k0               \n",
  "      ___                                                                                 W0l:::::;'.''';;;;;;;;;;;;;;;;;;:looooc:cc::lO               \n",
  "     |   \\  _ _  ___  __ _  _ __   ___                                                      XOdoool,.'.''.''''''''''''.''',coooooooodOX               \n",
  "     | |) || '_|/ -_)/ _` || '  \\ (_-/                                                         XOdoo:'..''''''..''''''..''':ooooooodOX                \n",
  "     |___/ |_|  \\___|\\__/_||_|_|_|/__/                                                           XOdl:'''''''''''''''.'''':oooooodkX                 \n",
  "                                                                                                  XOdl;,'.'''''''''''',;cooooodOX                      \n",
  "                                                                                                    XOdl:;,''''''',,;:looooodkX                        \n",
  "                                                                                                      XOdollcccclllloooooodOX                          \n",
  "                                                                                                        XOdooooooooooooodOX                            \n",
  "                                                                                                          XOdooooooooodOX                              \n",
  "                                                                                                            XOdooooodOX                                \n",
  "                                                                                                              XOdodOX                                  \n",
  "                                                                                                               WNXNW                                   \n");


  //continue here
  bool continue_program = true;

  while(continue_program){
    char user_choice = -1; char helper_char = -1;
    printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n%s", 
           "  Please choose one of the options below:",
           "  1-) Lexiographic order between two words",
           "  2-) Directed-braid (first relation)",
           "  3-) Directed-braid (second relation)",
           "  4-) Find natural basic word of a given reduced word",
           "  5-) Find natural word of a given reduced word",
           "  6-) Apply restricted-shuffle between two words",
           "  7-) Find the set reduced words of a permutation from a given reduced word",
           "  Enter a number[1-7] : ");

    user_choice = getc(stdin);
    helper_char = getc(stdin);
    if(user_choice - 48 < 1 || user_choice -48 > 7 || helper_char != '\n'){
        cout << "  The input should contain only numbers! [1-7]\n";
        exit(0);
    }
    if(user_choice == '1'){
      vector<vector<int>> words = standart_prompt();
      vector<int> word1 = words[0]; vector<int> word2 = words[1];

      bool res = check_lexiographic(word1, word2);
      if(res){
        printf("  Yes ->  "); print_word(word1); printf(" <lex "); print_word(word2); printf("\n");
      }
      else{
        printf("  No ->  "); print_word(word1); printf(" </lex "); print_word(word2); printf("\n");
      }
    }
    
    else if(user_choice == '2'){
      vector<vector<int>> words = standart_prompt();
      vector<int> word1 = words[0]; vector<int> word2 = words[1];
      bool res = check_relation1(word1, word2);
      if(res){
        printf("  Yes ->  "); print_word(word1); printf(" <1 "); print_word(word2); printf("\n");
      }
      else{
        printf("  No ->  "); print_word(word1); printf(" </1 "); print_word(word2); printf("\n");
      }
    }

    else if(user_choice == '3'){
      vector<vector<int>> words = standart_prompt();
      vector<int> word1 = words[0]; vector<int> word2 = words[1];
      bool res = check_relation2(word1, word2);
      if(res){
        printf("  Yes ->  "); print_word(word1); printf(" <2 "); print_word(word2); printf("\n");
      }
      else{
        printf("  No ->  "); print_word(word1); printf(" </2 "); print_word(word2); printf("\n");
      }
    }

    else if(user_choice == '6'){
      vector<vector<int>> words = standart_prompt();
      vector<int> word1 = words[0]; vector<int> word2 = words[1];
      vector<vector<int>> shuffles = restricted_shuffle_base(word1, word2);
      printf("%s%lu%s", "  There are ", shuffles.size(), " many combinations: \n\n");
      print_decomposition(shuffles);
    }

    else if(user_choice == '4'){
      vector<int> word = word_prompt();
      //the extreme case
      vector<vector<int>> res;
      auto decomposed_word = tower_decomposition(word);
      if(decomposed_word.size() == 1) res = decomposed_word;
      else res = selection_sort(decomposed_word); 
      printf("  Here is the corresponding natural basic word: "); print_decomposition(res);
    }

    else if(user_choice == '5'){
      vector<int> word = word_prompt();
      //the extreme case
      vector<vector<int>> res;
      auto decomposed_word = tower_decomposition(word);
      if(decomposed_word.size() == 1) res = decomposed_word;
      else res = insertion_sort(selection_sort(decomposed_word));
      printf("  Here is the corresponding unique natural word: "); print_decomposition(res);
    }

    else if(user_choice == '7'){
      char output_place = -1; char terminating_char = -1;
      printf("\n%s\n%s\n", "  NOTE: The program expects that the user will provide a REDUCED",
                         "  word below, it is assumed that it represents the permutation you wish to investigate.");
      vector<int> word = word_prompt(); 
      //commented parts was just used in time testing, not essential to the program
      //auto start = std::chrono::high_resolution_clock::now();
      auto res = reduced_words(tower_decomposition(word));
      //auto stop = std::chrono::high_resolution_clock::now();
      //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);     
      //cout << duration.count() << endl;
      printf("%s", "  Do you wish to output the result to [t]erminal, or a [f]ile? [t-f] : ");
      output_place = getc(stdin); terminating_char = getc(stdin);
      if(terminating_char != '\n' || (output_place != 'T' && output_place != 't' && output_place != 'f' && output_place != 'F')){
        printf("  Please only use 't' or 'f'.\n");
        exit(0);
      }

      if(output_place == 't' || output_place == 'T'){
        printf("\n%s%lu%s\n", "  There are ", res.size(), " many reduced words:\n");
        print_decomposition(res);
      }

      else{
        printf("\n%s\n%s\n%s\n\n%s\n%s", "  REMARK: The program will create a .txt file in the same directory",
                                     "  that is being executed, any file with the same name will be overwritten.",
                                     "  Use with caution. The name can be maximum 50 characters.",
                                     "  Allowed characters other than eng. letters: ' - ' and ' _ '",
                                     "  Please specify a file name, only eng. letters, no file extensions, no spaces: ");
        char *file_name = new char[56];
        for(int i = 0; i < 51; i++){
          char temp_char = getc(stdin);
          if(temp_char >= 65 && temp_char <= 90) file_name[i] = temp_char;
          else if(temp_char >= 97 && temp_char <= 122) file_name[i] = temp_char;
          else if(temp_char >= 48 && temp_char <= 57) file_name[i] = temp_char;
          else if(temp_char == 45 || temp_char == 95) file_name[i] = temp_char; //adds '-' and '_'
          else if(temp_char == '\n'){
            //adds the file extention
            file_name[i] = '.'; file_name[i+1] = 't'; file_name[i+2] = 'x'; file_name[i+3] = 't';
            break;
          }
          else{
            printf("%s%c%s\n", "  The character: ", temp_char, " is not allowed in a file name.\n");
            delete[] file_name;
            exit(0);
          }
          if(i == 50){
            printf("  The name you entered is longer than 50 characters.\n");
            delete[] file_name;
            exit(0);
          }
        }
        FILE* ifp = fopen(file_name, "w");
        fprintf(ifp, "%s%lu%s\n", "  There are ", res.size(), " many reduced words:\n");
        for(int i = 0; i < res.size(); i++){
          for(int j = 0; j < res[i].size(); j++){
            fprintf(ifp, "%d", res[i][j]);
          }
          if((i+1) % MAX_COLUMN == 0) fprintf(ifp, "%c", '\n');
          else fprintf(ifp, "%c", ' ');
        }
        if(res.size() % 5 != 0) fprintf(ifp, "%c", '\n');
        printf("\n%s%s\n", "  The result has been successfully written to the file: ", file_name);
        delete[] file_name;
      }    
    }
    
    printf("\nDo you wish to go back to the main [m]enu or [q]uit ? [m-q] : ");
    user_choice = getc(stdin); helper_char = getc(stdin);
    if(user_choice != 'm' && user_choice != 'M') continue_program = false; 
  }
}
