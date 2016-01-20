//
//  utilities.hpp
//  rocks
//
//  Created by Chuyue Zhang on 11/9/15.
//  Copyright © 2015 Camille Zhang. All rights reserved.
//

// utilities.h

const int MINWORDLEN = 4;
const int MAXWORDLEN = 6;

int loadWords(char words[][MAXWORDLEN+1], int maxWords);
int randInt(int min, int max);