#include "Jpeg.h"

bool loadJPEG(char* fileName, unsigned long &_x, unsigned long &_y, vector<int> &dataImage, int &maxHeight)
{
	cout << endl<< fileName << endl;
	FILE* file = fopen(fileName, "rb");  //open the file
	struct jpeg_decompress_struct info;  //the jpeg decompress info
	struct jpeg_error_mgr err;           //the error handler

	info.err = jpeg_std_error(&err);     //tell the jpeg decompression handler to send the errors to err
	jpeg_create_decompress(&info);       //sets info to all the default stuff
	
	//if the jpeg file didnt load exit
	if(!file)
	{
		cout << "Error reading JPEG file " << fileName << " !!!" << endl;
		return false;
	}

	jpeg_stdio_src(&info, file);    //tell the jpeg lib the file we'er reading

	jpeg_read_header(&info, TRUE);   //tell it to start reading it
	
	jpeg_start_decompress(&info);    //decompress the file

	//set the x and y
	_x = info.output_width;
	_y = info.output_height;
	int channels = info.num_components;

	int type = GL_RGB;
	if(channels == 4)
	{
		type = GL_RGBA;
	}
	if(channels == 1) {
		type = GL_BACK;
	}

	int bpp = channels * 8;
	
	int size = _x * _y;

	//read turn the uncompressed data into something ogl can read
	GLbyte *texData = new GLbyte[size*channels];      //setup data for the data its going to be handling
	dataImage.clear();

	GLbyte* p1 = texData;
	GLbyte** p2 = &p1;
	int numlines = 0;

	while(info.output_scanline < info.output_height)
	{
		numlines = jpeg_read_scanlines(&info, (JSAMPLE**)p2, 1);
		*p2 += numlines * channels * info.output_width;
	}

	jpeg_finish_decompress(&info);   //finish decompressing this file

	// On récupère le niveau de gris de l'image dans un tableau d'entier
	// Les données du fichier JPG sont codées sur 8 bit en tant qu'entier non signés
	// On ne peut pas directement les convertir en unsigned int car ce type est codé sur plus de 8 bits
	// On passe donc par le type unsigned char sur 8 bits, puis on reconverti la valeur obtenue en int
	
	maxHeight = 0;
	for(int i=0; i<_x*_y; i++) {
		dataImage.push_back((int)(unsigned char)texData[i*channels]);     // L'indice est i*3 car on ne prend que 1 donnée sur 3 étant donné que pour une image en nuance de gris, les valeurs r,g et b sont identiques
		checkMax(dataImage[i], maxHeight);     // On met à jour la hauteur maximale de la heightmap
	}

	fclose(file);                    //close the file

	return true;
}

void saveJPEG(char* fileName, unsigned long &_x, unsigned long &_y, vector<int> &dataImage, int maxGray) {
	FILE* outfile = fopen(fileName, "wb");

	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
 
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outfile);
 
	cinfo.image_width = _x;
	cinfo.image_height = _y;
	cinfo.input_components = 1;
	cinfo.in_color_space = JCS_GRAYSCALE;

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality (&cinfo, 75, true);
	jpeg_start_compress(&cinfo, true);

	JSAMPROW row_pointer;          // Pointeur vers une colonne
	unsigned char *image_buffer= new unsigned char[_x*_y];

	for(int i = 0; i < _x*_y; i++) {
		image_buffer[i] = (unsigned char) ((float)dataImage[i]*255.0/(float)maxGray);     // Ecriture des données dans le buffer
	}
	
	int row_stride = _x; /* JSAMPLEs per row in image_buffer */
 
	while (cinfo.next_scanline < cinfo.image_height) {
    /* jpeg_write_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could pass
     * more than one scanline at a time if that's more convenient.
     */
		row_pointer =  &(JSAMPLE) image_buffer[cinfo.next_scanline * row_stride];
		(void) jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }

	jpeg_finish_compress(&cinfo);
}

void checkMax(int level, int &maxHeight) {
	// Changement de maxHeight si level>maxHeight
	if(level > maxHeight)
		maxHeight = level;
}

bool loadHeightMap(char* fileName)
{
	loadJPEG(fileName, x, y, grayLevel, maxHeight);     // On récupère les données de l'image dans grayLevel

	// Redéfinition de la taille de l'éditeur
	editorHeight = EDITOR_HEIGHT;
	editorWidth = EDITOR_WIDTH;
	if((float)x/(float)editorWidth > (float)y/(float)editorHeight) {
		editorHeight = (int)((float)y*(float)editorWidth/(float)x);
	}
	else {
		editorWidth = (int)((float)x*(float)editorHeight/(float)y);
	}

	rapportPixel = (float)editorWidth/(float)x;

	return true;
}

void saveHeightMap(char* fileName) {
	saveJPEG(fileName, x, y, grayLevel, maxHeight);
}

char* openFileExplorer() {
	int res;
	OPENFILENAME ofn;
	TCHAR tmp[1024] ;
	tmp[0]= '\0' ;
	ZeroMemory ( &ofn , sizeof ( OPENFILENAMEW ) );
	ofn.lStructSize = sizeof ( OPENFILENAMEW );
	ofn.lpstrFile = tmp;
	ofn.nMaxFile = 1024;
	ofn.lpstrTitle = _T("Choisissez une image");
	ofn.lpstrFilter = _T("Tous (*.*)\0*.*\0Images (*.jpg)\0*.JPG\0");
	ofn.Flags = OFN_LONGNAMES | OFN_EXPLORER; // | OFN_ALLOWMULTISELECT  ;
	res = GetOpenFileName(&ofn); 

	if(res) {
		// Recherche de la taille du JPG
		int size = 0;
		while((char)tmp[size]!= '\0') {
			size++;
		}

		// Récupération des données du JPG
		char* fileName = new char[size+1];
		for(int i = 0; i < size; i++) {
			fileName[i] = (char)tmp[i];
		}
		fileName[size] = '\0';

		return fileName;
	}

	return "error";
}