#ifndef SPLINE_H
#define SPLINE_H

#include "FVec2.hpp"
#include "FVec3.hpp"

#include "FString.hpp"

#define SPLINE_LINEAR 0x001
#define SPLINE_CLOSED 0x002
#define SPLINE_MANUAL_TANGENTS 0x004

#define SPLINE_EPSILON 0.0001f
#define SPLINE_SHORT_STEP 0.01f

#define SPLINE_3D_LINEAR 0x001
#define SPLINE_3D_CLOSED 0x002
#define SPLINE_3D_MANUAL_TANGENTS 0x004
#define SPLINE_3D_EPSILON 0.0001f
#define SPLINE_3D_SHORT_STEP 0.01f

class FFile;
class FSpline {
public:
	FSpline(void);
	virtual ~FSpline(void);
    
    void                    Clone(FSpline *pFSpline);

	//Add points to the spline.
	void					Add(float x,float y);
	//inline void				Add(float x,int y){Add(x,(float)y);}
	//inline void				Add(int x,float y){Add((float)x,y);}
	//inline void				Add(int x,int y){Add((float)x,(float)y);}
	//inline void				AddPoint(float x,float y){Add(x,y);}
	//inline void				AddPoint(float x,int y){Add(x,(float)y);}
	//inline void				AddPoint(int x,float y){Add((float)x,y);}
	//inline void				AddPoint(int x,int y){Add((float)x,(float)y);}
	//inline void				Add(double x, double y){Add((float)x,(float)y);}
    
	//Framework specific.
	inline void				Add(FVec2 p){Add(p.mX,p.mY);}
	inline void				AddPoint(FVec2 p){Add(p.mX,p.mY);}
	inline void				operator+=(FVec2 theFVec2){Add(theFVec2);}
	//-

	//Manually set the tangent of the spline at a given index.
	//(Do this before solving the spline - a smooth curve will
	//be generated that is 'tugged' in the direction of the tangent
	//by the magnitude of the tangent).
	//Note: The spline also uses more memory once this has been called.
	void					SetTangent(int theIndex,float xtan,float ytan);
	inline void				SetTangent(int theIndex,int xtan,int ytan){SetTangent(theIndex,(float)xtan,(float)ytan);}
	inline void				SetTangent(int theIndex,float xtan,int ytan){SetTangent(theIndex,xtan,(float)ytan);}
	inline void				SetTangent(int theIndex,int xtan,float ytan){SetTangent(theIndex,(float)xtan,ytan);}
	//Framework specific
	inline void				SetTangent(int theIndex,FVec2 tan){SetTangent(theIndex,tan.mX,tan.mY);}
	//
	
    /*
	//Maybe we wanna add a point AND set a tangent for it!
	inline void				Add(float x, float y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, float y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, float y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, float y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, int y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, int y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, int y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(float x, int y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, float y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, float y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, float y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, float y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, int y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, int y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, int y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				Add(int x, int y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, float y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, float y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, float y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, float y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, int y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, int y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, int y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(float x, int y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, float y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, float y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, float y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, float y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, int y, float tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, int y, float tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, int y, int tanx, float tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	inline void				AddPoint(int x, int y, int tanx, int tany){AddPoint(x,y);SetTangent(mPointCount-1,tanx,tany);}
	*/
    
    ////
    //
	//Framework specific
    //
    ////
    
    /*
	inline void				Add(FVec2 p, FVec2 tan){Add(p.mX,p.mY,tan.mX,tan.mY);}
	inline void				Add(FVec2 p, float tanx, float tany){Add(p.mX,p.mY,tanx,tany);}
	inline void				Add(FVec2 p, int tanx, float tany){Add(p.mX,p.mY,tanx,tany);}
	inline void				Add(FVec2 p, float tanx, int tany){Add(p.mX,p.mY,tanx,tany);}
	inline void				Add(FVec2 p, int tanx, int tany){Add(p.mX,p.mY,tanx,tany);}
	inline void				Add(float x, float y, FVec2 tan){Add(x,y,tan.mX,tan.mY);}
	inline void				Add(int x, float y, FVec2 tan){Add(x,y,tan.mX,tan.mY);}
	inline void				Add(float x, int y, FVec2 tan){Add(x,y,tan.mX,tan.mY);}
	inline void				Add(int x, int y, FVec2 tan){Add(x,y,tan.mX,tan.mY);}
	inline void				AddPoint(FVec2 p, FVec2 tan){AddPoint(p.mX,p.mY,tan.mX,tan.mY);}
	inline void				AddPoint(FVec2 p, float tanx, float tany){AddPoint(p.mX,p.mY,tanx,tany);}
	inline void				AddPoint(FVec2 p, int tanx, float tany){AddPoint(p.mX,p.mY,tanx,tany);}
	inline void				AddPoint(FVec2 p, float tanx, int tany){AddPoint(p.mX,p.mY,tanx,tany);}
	inline void				AddPoint(FVec2 p, int tanx, int tany){AddPoint(p.mX,p.mY,tanx,tany);}
	inline void				AddPoint(float x, float y, FVec2 tan){AddPoint(x,y,tan.mX,tan.mY);}
	inline void				AddPoint(int x, float y, FVec2 tan){AddPoint(x,y,tan.mX,tan.mY);}
	inline void				AddPoint(float x, int y, FVec2 tan){AddPoint(x,y,tan.mX,tan.mY);}
	inline void				AddPoint(int x, int y, FVec2 tan){AddPoint(x,y,tan.mX,tan.mY);}
    */
	//

	//FSpline Editor functions!
	//
	//
	//Add a point at a given index. (later points
	//automatically pushed back)
	void					Insert(int theIndex,float x, float y);
    
    /*
	inline void				Insert(int theIndex,float x, int y){Insert(theIndex,x,(float)y);}
	inline void				Insert(int theIndex,int x, float y){Insert(theIndex,(float)x,y);}
	inline void				Insert(int theIndex,int x, int y){Insert(theIndex,(float)x,(float)y);}
	inline void				InsertPoint(int theIndex,float x, float y){Insert(theIndex,x,y);}
	inline void				InsertPoint(int theIndex,float x, int y){Insert(theIndex,x,(float)y);}
	inline void				InsertPoint(int theIndex,int x, float y){Insert(theIndex,(float)x,y);}
	inline void				InsertPoint(int theIndex,int x, int y){Insert(theIndex,(float)x,(float)y);}

	//Framework specific
	inline void				Insert(int theIndex,FVec2 p){Insert(theIndex,p.mX,p.mY);}
	inline void				InsertPoint(int theIndex,FVec2 p){Insert(theIndex,p.mX,p.mY);}
    */
	//

	//Change the position of a point already on the spline.
	void					SetPoint(int theIndex,float x, float y);
    
    /*
	inline void				SetPoint(int theIndex,float x, int y){SetPoint(theIndex,x,(float)y);}
	inline void				SetPoint(int theIndex,int x, float y){SetPoint(theIndex,(float)x,y);}
	inline void				SetPoint(int theIndex,int x, int y){SetPoint(theIndex,(float)x,(float)y);}

	inline void				MovePoint(int theIndex,float x, float y){SetPoint(theIndex,x,y);}
	inline void				MovePoint(int theIndex,float x, int y){SetPoint(theIndex,x,(float)y);}
	inline void				MovePoint(int theIndex,int x, float y){SetPoint(theIndex,(float)x,y);}
	inline void				MovePoint(int theIndex,int x, int y){SetPoint(theIndex,(float)x,(float)y);}

	//Framework specific
	inline void				SetPoint(int theIndex,FVec2 p){SetPoint(theIndex,p.mX,p.mY);}
	inline void				MovePoint(int theIndex,FVec2 p){SetPoint(theIndex,p.mX,p.mY);}
    */
	//


	//DON'T USE THIS UNLESS YOU KNOW WHAT YOU'RE DOING
	void					SetCoefs(int theIndex, float xa, float xb, float xc, float ya, float yb, float yc);
	inline void				SetCoefs(int theIndex, double xa, double xb, double xc, double ya, double yb, double yc){SetCoefs(theIndex,(float)xa,(float)xb,(float)xc,(float)ya,(float)yb,(float)yc);}


	void					InvertH(float theCenter);


	void					Translate(float theXDistance, float theYDistance);
	inline void				Translate(FVec2 theDistance){Translate(theDistance.mX,theDistance.mY);}


	//Removes the point/tangent at a given index.
	void					Delete(int theIndex);
    
	//
	//End editor functions!

	//Change the number of points the spline can hold.
	//If you Size() the spline the the number of points you will add
	//before you add them, it will be faster.
	//You can also remove end-points by shrinking the size.
	void					Size(int size);


	//file contents as argument! (must be null terminated)
	void					ImportData(char *theData);

    void                    Reset();
    void                    RemoveAll();
    
    
    
	//Destroy the spline and free up memory.
	void					Clear();

	//Solve() or CalculateFSpline() will generate the actual spline.
	//This should be called after all of the points are added and
	//all of the manual tangents are set!
	//
	//Circular means that the spline will be closed (The last point will be
	//connected to the first point by a smooth curve)
	//
	virtual void			Solve(bool linear=false,bool circular=false);
	//
	//***
	//Everything beyond this point should only be used
	//after Solve() or CalculateFSpline() have been called!
	//***
	//
    
	//Fetch a point along the spline. [Min() to Max()] AKA [0 to mPointCount-1]
	//Get(2.5) will yield the point interpolated half-way
	//between the 2nd and 3rd points that were added.
	void					Get(float pos,float &x,float &y);
	void					Get(int pos,float &x,float &y);
	float					GetX(float pos);//{float aX,aY;Get(pos,aX,aY);return aX;}
	float					GetY(float pos);//{float aX,aY;Get(pos,aX,aY);return aY;}
	//Framework specific.
	inline FVec2			Get(float pos){FVec2 aResult;Get(pos,aResult.mX,aResult.mY);return aResult;}
	inline FVec2			Get(int pos){FVec2 aResult;Get(pos,aResult.mX,aResult.mY);return aResult;}
	inline void				GetPoint(float pos,float &x,float &y){Get(pos,x,y);}
	inline void				GetPoint(int pos,float &x,float &y){Get(pos,x,y);}
	inline FVec2			GetPoint(float pos){FVec2 aResult;Get(pos,aResult.mX,aResult.mY);return aResult;}
	inline FVec2			GetPoint(int pos){FVec2 aResult;Get(pos,aResult.mX,aResult.mY);return aResult;}
	inline FVec2			operator[](float theSlot){return Get(theSlot);}
	inline FVec2			operator[](int theSlot){return Get(theSlot);}
	//

	//Find the closest position (or point) on the spline to a given point.
	//(This isn't extremely fast)
	float					GetClosestPosition(float x, float y, float &pDist);
	inline float			GetClosestPosition(float x, float y){float aDist;return GetClosestPosition(x,y,aDist);}
	inline float			GetClosestPosition(float x, int y){return GetClosestPosition((float)x,(float)y);}
	inline float			GetClosestPosition(int x, float y){return GetClosestPosition((float)x,y);}
	inline float			GetClosestPosition(int x, int y){return GetClosestPosition(x,(float)y);}
	
	//Framework specific.
	inline float			GetClosestPosition(FVec2 theFVec2){return GetClosestPosition(theFVec2.mX,theFVec2.mY);}
	inline FVec2			GetClosestPoint(FVec2 theFVec2){return GetClosestPoint(theFVec2.mX,theFVec2.mY);}
	
	inline FVec2			GetClosestPoint(FVec2 theFVec2, float &pDist){return Get(GetClosestPosition(theFVec2.mX,theFVec2.mY,pDist));}
	
	inline FVec2			GetClosestPoint(float x, float y){return Get(GetClosestPosition(x,y));}
	inline FVec2			GetClosestPoint(int x, int y){return GetClosestPoint((float)x,(float)y);}
	//

	int						GetClosestControlIndex(float x, float y, float &dist);

	//Get the tangent of the spline at a given position.
	void					Tan(float pos,float &x,float &y);
	void					Tan(int pos,float &x,float &y);
	//Framework specific.
	inline FVec2			Tan(int pos){FVec2 aResult;Tan(pos,aResult.mX,aResult.mY);return aResult;}
	inline FVec2			Tan(float pos){FVec2 aResult;Tan(pos,aResult.mX,aResult.mY);return aResult;}
	//

	//Get the length of the spline between two points
	//(end==-1 will seek to the end of the spline)
	//float					GetLength(float start=0,float end=-1);

	//Get the angle of the slope of the spline at a given position.
	float					Rot(float pos);
	inline float			Rotation(float pos){return Rot(pos);}

	//Steps along the spline by a given linear distance. Returns false when you pass
	//the end of the spline.
	bool					GetNextPoint(float &x, float &y, float &t,float theDistance=1.0f);
	bool					GetNextPointSloppy(float &x, float &y, float &t,float theDistance=1.0f);

	//The maximum and minimum positions of the spline.
	//for(float i=Min();i<=Max();i+=0.1f){}
	inline float			Max(){if(mChanged)Solve((mProperties&SPLINE_LINEAR)!=0,(mProperties&SPLINE_CLOSED)!=0);return (float)mMax;}
	inline float			Min(){return 0.0f;}
	
    
    int						mMax;

	bool					mChanged;
    
    float                   GetLength(float pStart,float pEnd);
    float                   LengthPredict(float pStepSpeed);
	

	//Info about the spline's last calculation.
	inline bool				IsClosed(){return (mProperties&SPLINE_CLOSED)!=0;}
	inline bool				IsCircular(){return IsClosed();}
	inline bool				IsLinear(){return (mProperties&SPLINE_LINEAR)!=0;}
	inline bool				IsUsingManualTangents(){return (mProperties&SPLINE_MANUAL_TANGENTS)!=0;}

	void					SetClosed(bool theState){mProperties&=(~SPLINE_CLOSED);if(theState)mProperties|=SPLINE_CLOSED;}
	void					SetLinear(bool theState){mProperties&=(~SPLINE_LINEAR);if(theState)mProperties|=SPLINE_LINEAR;}

	//Points that were added to the spline, stored as arrays of floats!
	float					*mX;
	float					*mY;
    //Number of points that were added to the spline.
	int						mPointCount;
	inline int				PointCount(){return mPointCount;}
    
    
    void                    Save(FFile *pFFile);
    void                    Load(FFile *pFFile);
    
    
    

	//Internal affairs.
//protected:
	void					Solve(float *theCoordinate,float*theDelta,float*theDerivative,float*theTemp,float*theCoef,bool linear,bool circular);
	void					Solve(float *theCoordinate,float*theDelta,float*theDerivative,float*theCoef,bool linear,bool circular);
	int						mSize;
	float					*mXCoef;
	float					*mYCoef;
	float                   *mTangent;
    
    float                   *mStorageDelta;
    float                   *mStorageTemp;
    
    
    
	float					mLength;
	unsigned int			mProperties;
    
};






class FSpline3D
{
public:
    FSpline3D(void);
    virtual ~FSpline3D(void);
    
    //Add points to the spline.
    void					Add(float x,float y,float z);
    
    //Manually set the tangent of the spline at a given index.
    //(Do this before solving the spline - a smooth curve will
    //be generated that is 'tugged' in the direction of the tangent
    //by the magnitude of the tangent).
    //Note: The spline also uses more memory once this has been called.
    void					SetTangent(int theIndex,float xtan,float ytan,float ztan);
    
    //Maybe we wanna add a point AND set a tangent for it!
    inline void				Add(float x, float y, float z, float tanx, float tany, float tanz){Add(x,y,z);SetTangent(mPointCount-1,tanx,tany,tanz);}
    
    //Spline Editor functions!
    //Add a point at a given index. (later points
    //automatically pushed back)
    void					Insert(int theIndex,float x, float y, float z);
    
    //Change the position of a point already on the spline.
    void					SetPoint(int theIndex,float x, float y, float z);
    
    
    void					Translate(float theXDistance, float theYDistance, float theZDistance);
    
    
    //Removes the point/tangent at a given index.
    void					Delete(int theIndex);
    
    //
    //End editor functions!
    
    //Change the number of points the spline can hold.
    //If you Size() the spline the the number of points you will add
    //before you add them, it will be faster.
    //You can also remove end-points by shrinking the size.
    void					Size(int size);
    
    
    void                    Reset();
    
    //Destroy the spline and free up memory.
    void					Clear();
    
    //Solve() or CalculateSpline() will generate the actual spline.
    //This should be called after all of the points are added and
    //all of the manual tangents are set!
    //
    //Circular means that the spline will be closed (The last point will be
    //connected to the first point by a smooth curve)
    //
    virtual void			Solve(bool linear=false,bool circular=false);
    //
    //***
    //Everything beyond this point should only be used
    //after Solve() or CalculateSpline() have been called!
    //***
    //
    
    //Fetch a point along the spline. [Min() to Max()] AKA [0 to mPointCount-1]
    //Get(2.5) will yield the point interpolated half-way
    //between the 2nd and 3rd points that were added.
    void					Get(float pos,float &x,float &y,float &z);
    void					Get(int pos,float &x,float &y,float &z);
    
    float					GetX(float pos);//{float aX,aY;Get(pos,aX,aY);return aX;}
    float					GetY(float pos);//{float aX,aY;Get(pos,aX,aY);return aY;}
    float					GetZ(float pos);//{float aX,aY;Get(pos,aX,aY);return aY;}
    
    //Framework specific.
    inline FVec3			Get(float pos){FVec3 aResult;Get(pos,aResult.mX,aResult.mY,aResult.mZ);return aResult;}
    
    //
    int						GetClosestControlIndex(float x, float y, float z, float &dist);
    
    //Get the tangent of the spline at a given position.
    void					Tan(float pos, float &x, float &y, float &z);
    void					Tan(int pos, float &x, float &y, float &z);
    
    FVec3                   Tan(float pPos);
    FVec3                   Perp(float pPos);
    FVec3                   Perp(float pPos, float pAngle);
    
    
    //The maximum and minimum positions of the spline.
    //for(float i=Min();i<=Max();i+=0.1f){}
    inline float			Max(){if(mChanged)Solve((mProperties&SPLINE_3D_LINEAR)!=0,(mProperties&SPLINE_3D_CLOSED)!=0);return (float)mMax;}
    inline float			Min(){return 0.0f;}
    int						mMax;
    
    bool					mChanged;
    
    //Info about the spline's last calculation.
    inline bool				IsClosed(){return (mProperties&SPLINE_3D_CLOSED)!=0;}
    inline bool				IsCircular(){return IsClosed();}
    inline bool				IsLinear(){return (mProperties&SPLINE_3D_LINEAR)!=0;}
    inline bool				IsUsingManualTangents(){return (mProperties&SPLINE_3D_MANUAL_TANGENTS)!=0;}
    
    void					SetClosed(bool theState){mProperties&=(~SPLINE_3D_CLOSED);if(theState)mProperties|=SPLINE_3D_CLOSED;}
    void					SetLinear(bool theState){mProperties&=(~SPLINE_3D_LINEAR);if(theState)mProperties|=SPLINE_3D_LINEAR;}
    
    //Points that were added to the spline, stored as arrays of floats!
    float					*mX;
    float					*mY;
    float					*mZ;
    
    //Number of points that were added to the spline.
    int						mPointCount;
    inline int				PointCount(){return mPointCount;}
    
    void					Solve(float *theCoordinate,float*theDelta,float*theDerivative,float*theTemp,float*theCoef,bool linear,bool circular);
    void					Solve(float *theCoordinate,float*theDelta,float*theDerivative,float*theCoef,bool linear,bool circular);
    int						mSize;
    
    float					*mXCoef;
    float					*mYCoef;
    float					*mZCoef;
    
    float					*mTangent;
    
    float                   *mStorageDelta;
    float                   *mStorageTemp;
    
    float					mLength;
    unsigned int			mProperties;    
};

#endif

