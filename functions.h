#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
//#include <chrono>

#define MAX_COLUMN 10

bool remove_duplicates2d_helper(std::vector<int> vec1, std::vector<int> vec2);

bool remove_duplicates3d_helper(std::vector<std::vector<int>> vec1, std::vector<std::vector<int>> vec2);

std::vector<std::vector<int>> remove_duplicates2d(std::vector<std::vector<int>> vec);

std::vector<std::vector<std::vector<int>>> remove_duplicates3d(std::vector<std::vector<std::vector<int>>> vec);

std::vector<std::vector<int>> tower_decomposition(std::vector<int> word);

std::vector<std::vector<int>> update_decomposition(std::vector<std::vector<int>> word_decomposed);

void print_word(std::vector<int> word);

void print_decomposition(std::vector<std::vector<int>> word_decomposed, int num = 5);

void print_passwords(std::vector<std::vector<std::vector<int>>> passwd);

std::vector<int> swap_place(std::vector<int> word, int index1, int index2);

bool check_relation1(std::vector<int> word1, std::vector<int> word2);

bool check_lexiographic(std::vector<int> word1, std::vector<int> word2);

bool check_relation2(std::vector<int> word1, std::vector<int> word2);

std::vector<std::vector<int>>selection_sort(std::vector<std::vector<int>> word_decomposed, std::vector<int> unwanted_indexes={-1});

std::vector<std::vector<int>>insertion_sort(std::vector<std::vector<int>> word_decomposed);

std::vector<std::vector<std::vector<int>>> passwords(int b, std::vector<std::vector<int>> word_decomposed);

std::vector<std::vector<std::vector<int>>> passwords_union(std::vector<std::vector<int>> word1_decomposed, std::vector<std::vector<int>> word2_decomposed);

std::vector<std::vector<std::vector<int>>> basic_words(std::vector<std::vector<int>> word_decomposed);

std::vector<std::vector<int>> restricted_shuffle_base(std::vector<int> word1, std::vector<int> word2);

std::vector<std::vector<int>> restricted_shuffle(std::vector<std::vector<int>> word_decomposed);

std::vector<std::vector<int>> reduced_words(std::vector<std::vector<int>> word_decomposed);

std::vector<std::vector<int>> standart_prompt(void);

std::vector<int> word_prompt(void);

#endif







