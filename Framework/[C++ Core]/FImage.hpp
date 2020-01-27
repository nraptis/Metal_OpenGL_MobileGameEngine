#ifndef FRAMEWORK_IMAGE_H
#define FRAMEWORK_IMAGE_H

#include "FString.hpp"

#define RGBA_TYPE 0
#define RGB_TYPE 1
#define ALPHA_TYPE 2

//It goes RGBA
//from bits 0...31

#define IMAGE_ALPHA_SHIFT(integer)((((unsigned int)integer)<<24)&0xFF000000)
#define IMAGE_ALPHA(color)(((color)>>24)&0xFF)
#define IMAGE_ALPHA_BITS (0xFF000000)
#define IMAGE_ALPHA_INVERSE (~IMAGE_ALPHA_BITS)

#define IMAGE_RED_SHIFT(integer)((((unsigned int)integer))&0x000000FF)
#define IMAGE_RED(color)(((color))&0xFF)
#define IMAGE_RED_BITS (0x000000FF)
#define IMAGE_RED_INVERSE (~IMAGE_RED_BITS)

#define IMAGE_GREEN_SHIFT(integer)((((unsigned int)integer)<<8)&0x0000FF00)
#define IMAGE_GREEN(color)(((color)>>8)&0xFF)
#define IMAGE_GREEN_BITS (0xFF000000)
#define IMAGE_GREEN_INVERSE (~IMAGE_GREEN_BITS)

#define IMAGE_BLUE_SHIFT(integer)((((unsigned int)integer)<<16)&0x00FF0000)
#define IMAGE_BLUE(color)(((color)>>16)&0xFF)
#define IMAGE_BLUE_BITS (0x00FF0000)
#define IMAGE_BLUE_INVERSE (~IMAGE_BLUE_BITS)

#define IMAGE_GREY(color)((IMAGE_RED(color) + IMAGE_GREEN(color) + IMAGE_BLUE(color)) / 3)

#define IMAGE_RGBA(__LOCAL_RED,__LOCAL_GREEN,__LOCAL_BLUE,__LOCAL_ALPHA) ((((unsigned int)__LOCAL_RED))&0x000000FF) | ((((unsigned int)__LOCAL_GREEN)<<8)&0x0000FF00) | ((((unsigned int)__LOCAL_BLUE)<<16)&0x00FF0000) | ((((unsigned int)__LOCAL_ALPHA)<<24)&0xFF000000)

#define IMAGE_INVERT_GREEN(color) (IMAGE_RGBA(IMAGE_RED(color), 255 - IMAGE_GREEN(color), IMAGE_BLUE(color), IMAGE_ALPHA(color)))



class FTexture;

class FImage
{
public:
	FImage();
	~FImage();
    
    void                            Load(char *pFile);
	inline void                     Load(const char *pFile) { Load((char*)pFile); }
	inline void                     Load(FString pFile){ Load(pFile.c()); }

    void                            LoadDirect(char *pFile);
	inline void                     LoadDirect(const char *pFile){LoadDirect((char*)pFile);}
	inline void                     LoadDirect(FString pFile){LoadDirect(pFile.c());}

    FTexture                        *GetTexture();
    
	void                            SetPixel(int x, int y, unsigned int pColor);
	void                            SetPixel(int x, int y, unsigned int pRed, unsigned int pGreen, unsigned int pBlue, unsigned int pAlpha=0xFF);
    
    void                            SetPixelBlendMax(int x, int y, unsigned int pColor);
	
	void                            MakeBlank(int pWidth, int pHeight);
	inline void                     MakeBlank(int pWidth, int pHeight, int pColor){MakeBlank(pWidth,pHeight);}
	void                            Make(int pWidth, int pHeight, int pColor);
	inline void                     Make(int pWidth, int pHeight){MakeBlank(pWidth, pHeight);}
	
	void                            Flood(int x, int y, int pWidth, int pHeight, int pRed, int pGreen, int pBlue, int pAlpha){Flood(x,y,pWidth,pHeight,IMAGE_RGBA(pRed, pGreen, pBlue, pAlpha));}
	void                            Flood(int x, int y, int pWidth, int pHeight, unsigned int pColor=0x000000FF);
	void                            Flood(unsigned int pColor=0x000000FF){Flood(0,0,mExpandedWidth,mHeight,pColor);}
    
    void                            Outline(int pSize=4, int pRed=0, int pGreen=0, int pBlue=0, int pAlpha=255);
    void                            OutlineRect(int x, int y, int pWidth, int pHeight, int pSize, unsigned int pColor);
    
    void                            FloodTransparent(int pColor);
	
	bool                            IsBlank();
    bool                            DidLoad();
	
	void                            Replace(unsigned int pOldColor, unsigned int pNewColor);
	void                            ReplaceAlpha(unsigned int pOldAlpha, unsigned int pNewColor);
	
	void                            ApplyGreyscaleAlpha(FImage *pImage);
    void                            ApplyGreyscaleAlphaInverse(FImage *pImage);

	void                            ExportBMP(char *pFile);
	inline void                     ExportBMP(FString pFile){ExportBMP(pFile.c());}
	
	void                            ExportRGB(char *pFile);
	inline void                     ExportRGB(FString pFile){ExportRGB(pFile.c());}
	
	void                            ExportA(char *pFile);
	inline void                     ExportA(FString pFile){ExportA(pFile.c());}
	
	void                            ExportACompressed(char *pFile);
	inline void                     ExportACompressed(FString pFile){ExportACompressed(pFile.c());}

    unsigned int                    **Get2DGrid();
    
    void                            DivideRGBA();
    void                            SubtractRGBA();
	
	void                            SubtractAlpha(int pAmount);
	
	//Incomplete, currently shiftf pixels 256 up....
	void                            ShiftPixels(int x, int y);
	
	void                            RotateLeft();
	void                            RotateRight();
	
	void                            FlipH();
	void                            FlipV();
	
	unsigned int                    GetColor(int x, int y);
	inline int                      GetAlpha(int x, int y){return IMAGE_ALPHA(GetColor(x,y));}
	
	void                            Stroke(unsigned int pColor, unsigned int pAlpha=128, int pSize=2, int pFade=1);
    
    void                            ExpandAllBorders(int pSize);
    
    void                            BufferEdges(int pSize);
    
    
    void                            PadLeft(int pSize);
    void                            PadRight(int pSize);
    void                            PadTop(int pSize);
    void                            PadBottom(int pSize);

    void                            Pad(int pPaddingLeft, int pPaddingRight, int pPaddingTop, int pPaddingBottom);

    void                            TrimLeft(int pSize);
    void                            TrimRight(int pSize);
    void                            TrimTop(int pSize);
    void                            TrimBottom(int pSize);
    
	void                            WhiteToAlpha();
	
	void                            Kill();
    
    FImage                          *Crop(int x, int y, int pWidth, int pHeight);
    FImage                          *Clone();
	
    
    //void                            FixTileBorders(int pX, int pY, int pWidth, int pHeight);
    void                            FixTileBorders(int pX, int pY, int pWidth, int pHeight, int pTimes);
    void                            FixTileBorders(int pBorderSize);
    
	
	void                            GetColorCentroid(int pRed, int pGreen, int pBlue, int &x, int &y, int pTolerance=10);
	
	void                            MakePowerOf2();
    
    void                            Invert();
	
	void                            Stamp(FImage *pImage, int x=0, int y=0);
	void                            StampBlend(FImage *pImage, int x=0, int y=0);
	void                            Stamp(unsigned int *pData, int x, int y, int pWidth, int pHeight);
	void                            Stamp(FImage *pImage,int x, int y,int pImageX, int pImageY=-1, int pImageWidth=-1, int pImageHeight=-1);
	void                            StampBlend(FImage *pImage,int x, int y,int pImageX, int pImageY=-1, int pImageWidth=-1, int pImageHeight=-1);
    
    void                            Resize(int theNewWidth, int theNewHeight, FImage *theImage);
    FImage                          *Resize50Percent();
    
	void                            GetEdges(int &pLeft, int &pRight, int &pTop, int &pBottom);
	
	int                             GetRight(int pCol);
	int                             GetLeft(int pCol);
	
	//void                          Bind();
	//void                          Rebind();
	
	void                            Print();
	
	FString                         mFileName;
	
	unsigned int                    *mData;
	int                             mExpandedWidth, mExpandedHeight;
	
	int                             mWidth, mHeight;
	int                             mOffsetX, mOffsetY;
    
    int                             mScale;
    
	//int                           mBindIndex;
    
};

unsigned int			            AverageColors(unsigned int pColor1, unsigned int pColor2);


#endif



