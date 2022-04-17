// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: Gray Scale Image Processor.cpp
// Last Modification Date: 4/5/2022
// Author1 and ID and Group: Sara Tamer Mohamed Bihery - 20210155 - S25
// Author2 and ID and Group: Farah Mohamed Mohamed El-Sayed - 20210288 - S25
// Author3 and ID and Group: Laila... - 20211072 - S....
// Teaching Assistant: Eng\ Mohamoud Fateaha
// Purpose: Making different filters on an image

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"


using namespace std;

unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];

void loadImage ();
void saveImage ();
void loadImage0();
void merge0();
void saveImage0();
void ImageBW ();
void ImageTranspose();
void ImageReverseVertical();
void ImageReverseHorizontal();
void darken1();
void lighten1();
void invert1();
void EdgeDetection();
void RightMirror();
void LeftMirror();
void UpperMirror();
void LowerMirror();
void Rotate90();
void Rotate180();
void Rotate270();
void Quarter1();
void Quarter2();
void Quarter3();
void Quarter4();
void Shuffle();


int main()
{
//    The menu display
    char choice , choice2;
    string choice3;

    cout << "Please select a filter to apply or 0 to exit:\n"
            "1- Black & White Filter\n"
            "2- Invert Filter\n"
            "3- Merge Filter \n"
            "4- Flip Image\n"
            "5- Rotate Image clockwise\n"
            "6- Darken or Lighten Image \n"
            "7- Detect Image Edges \n"
            "8- Enlarge Image\n"
            "9- Shrink Image\n"
            "a- Mirror 1/2 Image\n"
            "b- Shuffle Image\n"
            "c- Blur Image\n"
            "s- Save the image to a file\n"
            "0- Exit\n";
    cin >> choice;
    loadImage();
    if (choice == '1'){
        ImageBW ();
        saveImage ();
    }
    else if (choice == '2'){
        invert1();
        saveImage ();
    }
    else if (choice == '3'){
        loadImage0();
        merge0();
        saveImage0();
    }
    else if (choice == '4'){
        cout << "choose 'v' for vertical flip \nor 'h' for horizontal flip\n";
        cin >> choice2;

        if(choice2 == 'v'){
            ImageReverseVertical();
        }
        else if (choice2 == 'h'){
            ImageReverseHorizontal();
        }
        saveImage();
    }
    else if (choice == '5'){
        cout << "choose '1' for rotating 90 degrees, \n'2' for rotating 180 degrees or"
                "\n'3' for rotating 270 degrees\n";
        cin >> choice2;
        if (choice2 == '1'){
            Rotate90();
        }
        else if (choice2 == '2'){
            Rotate180();
        }
        else if ( choice2 == '3'){
            Rotate270();
        }
        saveImage ();
    }
    else if (choice == '6'){
        cout << "choose 'd' for Darken or 'l' for lighten\n";
        cin >> choice2;
        if(choice2 == 'd'){
            darken1();
        }
        else if (choice2 == 'l'){
            lighten1();
        }
        saveImage ();
    }
    else if (choice == '7'){
        EdgeDetection();
        saveImage ();
    }
    else if (choice == '8'){
        cout << "Choose 'q1' for the upper right quarter or\n"
                "q2 for the upper left quarter or\n"
                "q3 for the lower right quarter or \n"
                "q4 for the lower left quarter \n";
        cin >> choice3;
        if(choice3 == "q1"){
            Quarter1();
        }else if (choice3 == "q2")
            Quarter2();
        else if ( choice3 == "q3")
            Quarter3();
        else if (choice3 == "q4")
            Quarter4();
        saveImage0 ();
    }
    else if (choice == '9'){

        saveImage ();
    }
    else if (choice == 'a'){
        cout << "choose 'r' for right mirror ,\n 'f' for left mirror ,\n "
                "'u' for upper mirror or 'l' for lower mirror\n";
        cin >> choice2;
        if(choice2 == 'r'){
            RightMirror();
        }
        else if (choice2 == 'f'){
            LeftMirror();
        }
        else if ( choice2 == 'u'){
            UpperMirror();
        }
        else if ( choice2 == 'l'){
            LowerMirror();
        }
        saveImage ();
    }
    else if (choice == 'b'){
        cout << "Enter the pattern you need.\n";
//        Shuffle();
        saveImage ();
    }
    else if (choice == 'c'){

        saveImage ();
    }
    else if (choice == 's'){

        saveImage ();
    }
    else if (choice == '0'){
        return 0;
    }
    return 0;
}

void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: \n";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
}

void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name:\n ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

// Black and white function
void ImageBW (){
    long sum = 0 ,average = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            sum += image[i][j];
        }
        average = sum/(SIZE*SIZE);
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            if (image[i][j] > average)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}
// the transpose of the image is required to get the flipped filter
void ImageTranspose(){
    int n = 256;
    for (int i = 0; i < n ; i++) {
        for (int j = i; j< n; j++) {
            int temp = image[i][j];
            swap(image[i][j] , image[j][i]);
            image[j][i] = temp;
        }
    }
}
// then reverse the image on y-axis then transpose again to get the flipped filter
void ImageReverseVertical(){
    int n = 256;
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n/2; j++) {
            int temp = image[i][j];
            swap(image[i][j] , image[i][n-j-1]);
            image[i][n-j-1] = temp;
        }
    }
}
void ImageReverseHorizontal(){
    int n = 256;
    for (int i = 0; i < n/2 ; i++){
        for (int j = 0; j < n; j++){
            int temp = image[i][j];
            swap( image[i][j] , image[n-i-1][j]);
            image[n-i-1][j] = temp;
        }
    }
}
// function to deal with two images in case of merge
void loadImage0() {
//    char image1FileName[100];
    char image2FileName[100];

    // Get gray scale image file name
    cout << "Enter the source image2 file name: ";
    cin >> image2FileName;

    // Add to it .bmp extension and load image
    strcat (image2FileName, ".bmp");
    readGSBMP(image2FileName, image2);
}

//this function to merge image.
void merge0() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            image3[i][j] = (image[i][j] + image2[i][j])/2 ;


        }
    }
}
void saveImage0() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image3);
}
void darken1() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

            image[i][j] = (image[i][j]) /3;

        }
    }
}
void lighten1() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j] =  (image[i][j])/2 + 150/2 ;
        }
    }
}
void invert1() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j] = (image[i][j])* -1;
        }
    }
}
//function of edge detection
void EdgeDetection(){
//    call the black and white function to deal with
    ImageBW();
    for (int i = 0 ; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            //if the pixel and the next pixel (in row or column) are equal make them white else make them black
            if(image[i][j] != image[i+1][j] || image[i][j] != image[i][j+1]){
                image[i][j] = 0;
            }
            else {
                image[i][j] = 255;
                }
        }
    }
}
//function to mirror the right half
void RightMirror(){
    int n = 256;
    for (int i = 0 ; i < SIZE; i++){
        for (int j = 0; j < SIZE/2; j++) {
            image[i][j] = image[i][n-j-1];
        }
    }
}
//function to mirror the left half
void LeftMirror(){
    int n = 256;
    for (int i = 0 ; i < SIZE; i++){
        for (int j = SIZE/2; j < SIZE; j++) {
            image[i][j] = image[i][n-j-1];
        }
    }
}
//function to mirror the upper half
void UpperMirror(){
    int n = 256;
    for (int i = SIZE/2 ; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image[n-i-1][j];
        }
    }
}
//function to mirror the lower half
void LowerMirror(){
    int n = 256;
    for (int i = 0 ; i < SIZE/2; i++){
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = image[n-i-1][j];
        }
    }
}
void Rotate90(){
    ImageTranspose();
    ImageReverseVertical();
}
void Rotate180(){
    ImageReverseVertical();
    ImageReverseHorizontal();
}
void Rotate270(){
    ImageTranspose();
    ImageReverseHorizontal();
}
void Quarter1() {
//
//    for (int i = 0; i < SIZE / 2; i++) {
//        for (int j = 0; j < SIZE / 2; j++) {
//            image3[i][j] = image[i][j];
//        }
//    }
    for(int k = 0, i= 0 ; i<SIZE; k++, i+=2){
        for (int z = 0 , j = 0 ; j< SIZE; z ++, j +=2){
            image3[i][j] = image[k][z];
            image3[i+1][j] = image[k][z];
            image3[i+1][j+1] = image[k][z];
            image3[i][j+1] = image[k][z];

        }
    }
}
void Quarter2() {
//    for (int i = 0; i < SIZE / 2; i++) {
//        for (int j = SIZE / 2; j < SIZE; j++) {
//            image3[i][j] = image[i][j];
//        }
//    }
    for (int k = 0, i = 0; i < SIZE; k++, i += 2) {
        for (int z = 128, j = 0; j < SIZE; z++, j += 2) {
            image3[i][j] = image[k][z];
            image3[i + 1][j] = image[k][z];
            image3[i + 1][j + 1] = image[k][z];
            image3[i][j + 1] = image[k][z];

        }
    }
}
void Quarter3(){
//    for (int i = SIZE / 2; i < SIZE ; i++) {
//        for (int j = 0; j < SIZE / 2; j++) {
//            image3[i][j] = image[i][j];
//        }
//    }
    for (int k = 128, i = 0; i < SIZE; k++, i += 2) {
        for (int z = 0, j = 0; j < SIZE; z++, j += 2) {
            image3[i][j] = image[k][z];
            image3[i + 1][j] = image[k][z];
            image3[i + 1][j + 1] = image[k][z];
            image3[i][j + 1] = image[k][z];
        }
    }
}
void Quarter4(){
//    for (int i = SIZE / 2; i < SIZE; i++) {
//        for (int j = SIZE /2; j < SIZE ; j++) {
//            image3[i][j] = image[i][j];
//        }
//    }
    for (int k = 128, i = 0; i < SIZE; k++, i += 2) {
        for (int z = 128, j = 0; j < SIZE; z++, j += 2) {
            image3[i][j] = image[k][z];
            image3[i + 1][j] = image[k][z];
            image3[i + 1][j + 1] = image[k][z];
            image3[i][j + 1] = image[k][z];

        }
    }
}
