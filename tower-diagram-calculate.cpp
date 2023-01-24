#include "functions.h"
#include "tower-diagram.h"

using namespace std;

int main(void){
  auto user_vec = word_prompt(); 
  int max_val = *max_element(user_vec.begin(), user_vec.end());
  auto tower_diag = find_tower_diagram(user_vec, max_val);
  
  //to understand this part, please look at the function definition for find_tower_diagram
  if(tower_diag[max_val+1][0] == 'X') {printf("The word "); print_word(user_vec); printf(" is NOT reduced.\n");} 
  else {printf("The word "); print_word(user_vec); printf(" is reduced.\n");}
  printf("Its tower diagram:\n");
  for(int j = max_val-1; j >= 0; j--){
    for(int k = 0; k < max_val; k++){
      printf("%c", tower_diag[k][j]);
    }
    printf("\n");
  }
  
  printf("\nFor better visualization would you like save this data to a file?\n");
  printf("If you have SAGE installed, you can use the data with tower-diagram.sage [y-n]: ");
  char c, c_helper; c = getc(stdin); c_helper = getc(stdin);

  if(c_helper == '\n' && (c == 'y' || c == 'Y')){
    char* file_name = new char[81];
    for(int i = 0; i < user_vec.size(); i++){
      char temp_char = user_vec[i] + 48;
      file_name[i] = temp_char;
    }
    char file_ext[] = "-vertex.txt";
    for(int i = 0; i < 11; i++){
      file_name[user_vec.size() + i] = file_ext[i];
    }
    file_name[user_vec.size() + 11] = '\0'; //just for safety

    FILE* ifp = fopen(file_name, "w");
    //this part just outputs the data in tower_diag to the file
    for(int j = 0; j < max_val; j++){
      for(int k = 0; k < max_val; k++){
        if(tower_diag[j][k] == '*') fprintf(ifp, "%d %d\n", j, k);
      }
    }
    printf("Vertex data is written into the file %s\n", file_name);
    printf("To use it, execute ' sage tower-diagram.sage ' in the terminal\n and input the file name when the program asks.\n");
    delete[] file_name;  
  }

  //memory freeing part
  for(int j = 0; j < max_val + 2; j++){
    delete tower_diag[j];
  }
  delete[] tower_diag;

}

