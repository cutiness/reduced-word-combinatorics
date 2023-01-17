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

/*
    This file only contains the driver code for the program.
    For a more in depth view, please look at "functions.cpp"
*/

#include "functions.h"
#include "tower-diagram.h"
using namespace std;

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
      //if the given word is not reduced, we give a message to the user
      if(!is_reduced(word)){ printf("The word you entered is not a reduced word!"); exit(0);}

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
