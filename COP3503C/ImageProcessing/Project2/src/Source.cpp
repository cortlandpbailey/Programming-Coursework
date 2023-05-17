#include <iostream>
#include <fstream>
#include<vector>
#include<string>
#include "Image.h"

using namespace std;

Image* LoadTGA(ifstream& inFile);
void WriteTGA(Image* i, string filename);


int main() {

	cout << "Executing Program..." << endl;
	//Load all inputs
	ifstream inFile("input/layer1.tga", ios_base::in | ios_base::binary);			// Open file 1
	Image* layer1 = LoadTGA(inFile);												// Read and store file1
	inFile.close();																	// close file 1
	inFile.open("input/pattern1.tga", ios_base::in | ios_base::binary);				// open file 2
	Image* pattern1 = LoadTGA(inFile);												// Read and store file 2
	inFile.close();																	// close file 2
	inFile.open("input/layer2.tga", ios_base::in | ios_base::binary);				// open file 3
	Image* layer2 = LoadTGA(inFile);												// Read and store file 3
	inFile.close();																	// close file 3
	inFile.open("input/pattern2.tga", ios_base::in | ios_base::binary);				// open file 5
	Image* pattern2 = LoadTGA(inFile);												// Read and store file 5
	inFile.close();																	// close file 5
	inFile.open("input/car.tga", ios_base::in | ios_base::binary);					// open file 6
	Image* car = LoadTGA(inFile);													// Read and store file 6
	inFile.close();																	// close file 6
	inFile.open("input/circles.tga", ios_base::in | ios_base::binary);				// open file 7
	Image* circles = LoadTGA(inFile);												// Read and store file 7
	inFile.close();																	// close file 7
	inFile.open("input/layer_blue.tga", ios_base::in | ios_base::binary);			// open file 8
	Image* layerblue = LoadTGA(inFile);												// Read and store file 8
	inFile.close();																	// close file 8
	inFile.open("input/layer_green.tga", ios_base::in | ios_base::binary);			// open file 9
	Image* layergreen = LoadTGA(inFile);											// Read and store file 9
	inFile.close();																	// close file 9
	inFile.open("input/layer_red.tga", ios_base::in | ios_base::binary);				// open file 10
	Image* layerred = LoadTGA(inFile);												// Read and store file 10
	inFile.close();																	// close file 10
	inFile.open("input/text.tga", ios_base::in | ios_base::binary);					// open file 11
	Image* text = LoadTGA(inFile);													// Read and store file 11
	inFile.close();																	// close file 11
	inFile.open("input/text2.tga", ios_base::in | ios_base::binary);				// open file 4
	Image* text2 = LoadTGA(inFile);													// Read and store file 4
	inFile.close();													
	
	// Part 1: Multiply 2 layers
	Image* part1 = new Image();														// create new file - out 1
	part1->AddHeader(layer1->GetHeader());											// Add header that matches exactly to the input
	part1->Multiply(layer1, pattern1);												// do modifying 
	inFile.open("examples/EXAMPLE_part1.tga", ios_base::in | ios_base::binary);
	Image* example1 = LoadTGA(inFile);
	inFile.close();
	if (part1->Compare(*example1)) {
		WriteTGA(part1, "output/part1.tga");											// write to out 1
		cout << "Part 1 complete!" << endl;												// report out 1 complete
	}
	else {
		WriteTGA(part1, "output/part1.tga");											// write to out 1
		cout << "Part 1 not correct" << endl;
	}
		
	// Part 2: Subtract 2 layers
	Image* part2 = new Image();
	part2->AddHeader(layer2->GetHeader());
	part2->Subtract(layer2, car);
	inFile.open("examples/EXAMPLE_part2.tga", ios_base::in | ios_base::binary);
	Image* example2 = LoadTGA(inFile);
	inFile.close();
	if (part2->Compare(*example2)) {
		WriteTGA(part2, "output/part2.tga");											// write to out 2
		cout << "Part 2 complete!" << endl;												// report out 2 complete
	}
	else {
		WriteTGA(part2, "output/part2.tga");											// write to out 2

		cout << "Part 2 not correct" << endl;
	}
	
	// Part 3: Multiply and Screen
	Image* part3 = new Image();														// create new file - out 1
	part3->AddHeader(layer2->GetHeader());											// Add header that matches exactly to the input
	Image* temp = new Image();
	temp->AddHeader(layer2->GetHeader());
	temp->Multiply(layer1, pattern2);												// do modifying 
	part3->Screen(text, temp);
	inFile.open("examples/EXAMPLE_part3.tga", ios_base::in | ios_base::binary);
	Image* example3 = LoadTGA(inFile);
	inFile.close();
	if (part3->Compare(*example3)) {
		WriteTGA(part3, "output/part3.tga");											// write to out 1
		cout << "Part 3 complete!" << endl;												// report out 1 complete
	}
	else {
		WriteTGA(part3, "output/part3.tga");
		cout << "Part 3 not correct" << endl;
	}
	// Part 4: Multiply and subtract
	Image* part4 = new Image();														// create new file - out 1
	part4->AddHeader(layer2->GetHeader());											// Add header that matches exactly to the input
	part4->Multiply(layer2, circles);												// do modifying 
	part4->Subtract(pattern2, part4);
	inFile.open("examples/EXAMPLE_part4.tga", ios_base::in | ios_base::binary);
	Image* example4 = LoadTGA(inFile);
	inFile.close();
	if (part4->Compare(*example4)) {
		WriteTGA(part4, "output/part4.tga");											// write to out 1
		cout << "Part 4 complete!" << endl;												// report out 1 complete
	}
	else {
		WriteTGA(part4, "output/part4.tga");											// write to out 1
		cout << "Part 4 not correct" << endl;
	}
		

	// Part 5: Overlay
	Image* part5 = new Image();														// create new file - out 1
	part5->AddHeader(car->GetHeader());
	part5->Overlay(layer1, pattern1);
	inFile.open("examples/EXAMPLE_part5.tga", ios_base::in | ios_base::binary);
	Image* example5 = LoadTGA(inFile);
	inFile.close();
	if (part5->Compare(*example5)) {
		WriteTGA(part5, "output/part5.tga");											// write to out 1
		cout << "Part 5 complete!" << endl;												// report out 1 complete
	}
	else {
		WriteTGA(part5, "output/part5.tga");
		cout << "Part 5 not correct" << endl;
	}
	// Part 6: Add 200 to green channel
	Image* part6 = new Image();														// create new file - out 1
	part6->AddHeader(car->GetHeader());											// Add header that matches exactly to the input
	part6->Add(car, 0, 200, 0);
	inFile.open("examples/EXAMPLE_part6.tga", ios_base::in | ios_base::binary);
	Image* example6 = LoadTGA(inFile);
	inFile.close();
	if (part6->Compare(*example6)) {
		WriteTGA(part6, "output/part6.tga");											// write to out 1
		cout << "Part 6 complete!" << endl;												// report out 1 complete
	}
	else {
		WriteTGA(part6, "output/part6.tga");											// write to out 1
		cout << "Part 6 not correct" << endl;
	}
		
	
	// Part 7: Scale
	Image* part7 = new Image();														// create new file - out 1
	part7->AddHeader(car->GetHeader());											// Add header that matches exactly to the input
	part7->Multiply(car, 0, 1, 4);												// do modifying 
	inFile.open("examples/EXAMPLE_part7.tga", ios_base::in | ios_base::binary);
	Image* example7 = LoadTGA(inFile);
	inFile.close();
	if (part7->Compare(*example7)) {
		WriteTGA(part7, "output/part7.tga");											// write to out 1
		cout << "Part 7 complete!" << endl;												// report out 1 complete
	}
	else {
		WriteTGA(part7, "output/part7.tga");											// write to out 1
		cout << "Part 7 not correct" << endl;
	}

	// Part 8: Separate colors
	Image* part8_b = new Image();														// create new file - out 8
	part8_b->AddHeader(car->GetHeader());												// Add header that matches exactly to the input
	part8_b->Blue(car);																			// do modifying 
	Image* part8_g = new Image();
	part8_g->AddHeader(car->GetHeader());												// Add header that matches exactly to the input
	part8_g->Green(car);
	Image* part8_r = new Image();
	part8_r->AddHeader(car->GetHeader());												// Add header that matches exactly to the input
	part8_r->Red(car);
	inFile.open("examples/EXAMPLE_part8_b.tga", ios_base::in | ios_base::binary);
	Image* example8_b = LoadTGA(inFile);
	inFile.close();
	inFile.open("examples/EXAMPLE_part8_g.tga", ios_base::in | ios_base::binary);
	Image* example8_g = LoadTGA(inFile);
	inFile.close();
	inFile.open("examples/EXAMPLE_part8_r.tga", ios_base::in | ios_base::binary);
	Image* example8_r = LoadTGA(inFile);
	inFile.close();

	if (part8_b->Compare(*example8_b) && part8_g->Compare(*example8_g) && part8_r->Compare(*example8_r)) {
		WriteTGA(part8_b, "output/part8_b.tga");											// write to out 1
		WriteTGA(part8_g, "output/part8_g.tga");
		WriteTGA(part8_r, "output/part8_r.tga");
		cout << "Part 8 complete!" << endl;												// report out 1 complete
	}
	else {
		WriteTGA(part8_b, "output/part8_b.tga");											// write to out 1
		WriteTGA(part8_g, "output/part8_g.tga");
		WriteTGA(part8_r, "output/part8_r.tga"); 
		cout << "Part 8 not correct" << endl;
	}
		
	// Part 9: Combine layers
	Image* part9 = new Image();														// create new file - out 1
	part9->AddHeader(layergreen->GetHeader());											// Add header that matches exactly to the input
	part9->AddBlankPixels(238800);
	part9->Add(layerred, "red");
	part9->Add(layerblue, "blue");
	part9->Add(layergreen, "green");
	inFile.open("examples/EXAMPLE_part9.tga", ios_base::in | ios_base::binary);
	Image* example9 = LoadTGA(inFile);
	inFile.close();
	if (part9->Compare(*example9)) {
		WriteTGA(part9, "output/part9.tga");											// write to out 1
		cout << "Part 9 complete!" << endl;												// report out 1 complete
	}
	else {
				WriteTGA(part9, "output/part9.tga");											// write to out 1
				cout << "Part 9 not correct" << endl;
	}

	// Part 10: Flip
	Image* part10 = new Image();														// create new file - out 1
	part10->AddHeader(text2->GetHeader());											// Add header that matches exactly to the input
	part10->Flip(text2);
	inFile.open("examples/EXAMPLE_part10.tga", ios_base::in | ios_base::binary);
	Image* example10 = LoadTGA(inFile);
	inFile.close();
	if (part10->Compare(*example10)) {
		WriteTGA(part10, "output/part10.tga");											// write to out 1
		cout << "Part 10 complete!" << endl;												// report out 1 complete
	}
	else {
		WriteTGA(part10, "output/part10.tga");											// write to out 1
		cout << "Part 10 not correct" << endl;
	}
	
	


	//delete images created (destructors called)
	pattern1->~Image();
	pattern2->~Image();
	return 0;
}

//Function Definitions:
Image* LoadTGA(ifstream& inFile) {
	//Create new image in dynamic memory
	Image* newimage = new Image;
	//start with reading the header
	newimage->AddHeader(inFile);
	//Now add pixels data:
	newimage->addPixels(inFile);
	return newimage;
}

void WriteTGA(Image* i, string filename) {
	// Open up a new file 
	fstream outfile(filename, ios_base::out | ios_base::binary);
	i->WriteImage(outfile);
	outfile.close();
}
