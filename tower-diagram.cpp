/*
The GPLv3 License (GPLv3)

Copyright (c) 2023 cutiness

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

#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

//char tower_diagram[9][9];
bool is_reduced(vector<int> word){
  int max_val = *max_element(word.begin(), word.end());
  char tower_diagram[max_val+1][max_val+1];

  //initilasation of tower_diagram
  for(int i = 0; i < max_val; i++){
    for(int j = 0; j < max_val+1; j++){
      tower_diagram[i][j] = ((j == max_val) ? '\0' : ' ');
    }
  }
  for(int i = 0; i < max_val+1; i++) tower_diagram[max_val][i] = '\0';

  //finding the target block to start the zig-zag process
  //if that is not necessary we place the element directly
  for(int i = 0; i < word.size(); i++){
    int temp_val = word[i], zig_zag_index = -1, zig_zag_column = -1;
    for(int j = 0; j < temp_val; j++){
      // the case where the target square is at level zero is handled seperatly here
      if(temp_val -1 -j == 0 && tower_diagram[j][0] == ' '){ tower_diagram[j][0] = '*'; break;}
      else if(temp_val -1 -j == 0 && tower_diagram[j][0] == '*'){ 
        if(tower_diagram[j][1] == '*'){zig_zag_index = 0; zig_zag_column = j; break;}
        else return false;
      }
      //this is the case where we need to check the element below, above level 0
      else if(tower_diagram[j][(temp_val-1-j)] == '*'){
        if(tower_diagram[j][(temp_val-1-j) + 1] == '*'){ zig_zag_index = temp_val-1-j; zig_zag_column = j; break;}
        //the new added square destroys the old one here, no need to check further
        else return false;
      }
      //if there is no square blocking, then we check the element below to determine
      //whether or not the new square can be placed here
      else if(tower_diagram[j][(temp_val-1-j)-1] == '*'){ tower_diagram[j][(temp_val-1-j)] = '*'; break;}
    }

    if(zig_zag_index == -1) continue;
    
    //this condition can be potentially impossible, investigare further later on****
    if(zig_zag_column + 1 == max_val) return false; //impossible to do zig-zag to the last index
    
    //we do the zig-zag operation (if needed) here      
    for(int j = zig_zag_column + 1; j < max_val + 1; j++){
      //if there is another zig-zag possibility, we go to the next column
      if(tower_diagram[j][zig_zag_index == '*'] && tower_diagram[j][zig_zag_index+1] == '*') continue;
      //if the target place is occupied without the possibility of zig-zag, we terminate the process
      else if(tower_diagram[j][zig_zag_index] == '*') return false;
      //if the signal reached here then the target place is empty
      
      //if the target place is empty at the bottom level, we may insert the square
      else if(zig_zag_index == 0){ tower_diagram[j][zig_zag_index] = '*'; break;}

      //if the square below the target is occupied, we may put our new square there
      else if(tower_diagram[j][zig_zag_index-1] == '*'){ 
        tower_diagram[j][zig_zag_index] = '*'; break;
      }
      
      //if the signal reached here, we should have a target, where the square below is also empty
      //so we lover the zig-zag index by 1
      else zig_zag_index -= 1; 
    } 
  }      
  //if every square is placed without any interuption, nothing is wrong
  return true;
}

// int main(void){
//   vector<int> lul = {3,4,5,6,5,4,1,2,3,1,2,1};
//   if(is_reduced(lul)) printf("\nlulxd\n");
//   else printf("\nbruh\n");

//   for(int i = 7 ; i >= 0; i--){
//     for(int j = 0; j < 8; j++){
//       printf("%c", tower_diagram[j][i]);
//     }
//     printf("\n");
//   }

// }
