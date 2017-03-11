#if H
#define RGBlampAAN My_NEC.send(0xF7C03F)
#define RGBlampUIT My_NEC.send(0xF740BF)
#define RGBlampRED My_NEC.send(0xF720DF)
#define RGBlampGRN My_NEC.send(0xF7A05F)
#define RGBlampBLU My_NEC.send(0xF7609F)
#define RGBlampSMOOTH My_NEC.send(0xF7E917)

#else


//Lamp
#define l_up     0xF700FF // 9 levels
#define l_down   0xF7807F  // 9 levels
#define l_OFF    0xF740BF  
#define l_ON     0xF7C03F
#define l_RED    0xF720DF 
#define l_GRN    0xF7A05F  
#define l_BLU    0xF7609F  
#define l_WHITE  0xF7E01F
#define l_RED2   0xF710EF 
#define l_GRN2   0xF7906F  
#define l_BLU2   0xF750AF  
#define l_FLASH  0xF7D02F
#define l_RED3   0xF730CF 
#define l_GRN3   0xF7B04F  
#define l_BLU3   0xF7708F  
#define l_STROBE 0xF7F00F
#define l_RED4   0xF708F7 
#define l_GRN4   0xF78877  
#define l_BLU4   0xF748B7  //=GRN2 bij RGB strip ?
#define l_FADE   0xF7C837
#define l_RED5   0xF728D7 
#define l_GRN5   0xF7A857  
#define l_BLU5   0xF76897  
#define l_SMOOTH 0xF7E817 
// synonyms
#define l_ORANGE 0xF730CF //=RED3
#define l_YELLOW 0xF728D7 //=RED5
// standard defines
#define RGBlampAAN My_NEC.send(0xF7C03F)
#define RGBlampUIT My_NEC.send(0xF740BF)
#define RGBlampRED My_NEC.send(0xF720DF)
#define RGBlampGRN My_NEC.send(0xF7A05F)
#define RGBlampBLU My_NEC.send(0xF7609F)
#define RGBlampSMOOTH My_NEC.send(0xF7E917)
#endif
//RGB strip
#define strip_UP     0xFF906F
#define strip_DOWN   0xFFB847
#define strip_OFF    0xFFF807
#define strip_ON     0xFFB04F
#define strip_RED    0xFF9867 
#define strip_GRN    0xFFD827 
#define strip_BLU    0xFF8877  
#define strip_WHITE  0xFFA857
#define strip_RED2   0xFFE817
#define strip_GRN2   0xFF48B7  //=BLUE4 bij RGB lamp ?
#define strip_BLU2   0xFF6897 
#define strip_FLASH  0xFFB24D
#define strip_RED3   0xFF02FD 
#define strip_GRN3   0xFF32CD 
#define strip_BLU3   0xFF20DF 
#define strip_STROBE 0xFF00FF
#define strip_RED4   0xFF50AF
#define strip_GRN4   0xFF7887 
#define strip_BLU4   0xFF708F 
#define strip_FADE   0xFF58A7
#define strip_RED5   0xFF38C7
#define strip_GRN5   0xFF28D7  
#define strip_BLU5   0xFFF00F 
#define strip_SMOOTH 0xFF30CF

#define RGBstripAAN My_NEC.send(0xFFB04F)
#define RGBstripUIT My_NEC.send(0xFFF807)
#define RGBstripRED My_NEC.send(0xFF9867)
#define RGBstripGRN My_NEC.send(0xFFD827)
#define RGBstripBLU My_NEC.send(0xFF8877)

//http://blog.allgaiershops.com/2012/05/10/reversing-an-rgb-led-remote/
