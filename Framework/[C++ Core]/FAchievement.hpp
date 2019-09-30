
#ifndef FRAMEWORK_ACHIEVEMENT_HPP
#define FRAMEWORK_ACHIEVEMENT_HPP

#include "FFile.hpp"
#include "FList.hpp"

class FAchievement {
public:
    FAchievement(const char *pName, int pProgressMax);
    FAchievement();
    ~FAchievement();

    void                SetUp(const char *pName, int pProgressMax=1);
    
    //mName is also used as identifier for GameCenter or OpenFeint...
    FString				mName;
	
	virtual void		Load(FFile *pFFile);
	virtual void		Save(FFile *pFFile);
	
	virtual void		ResetProgress();
	virtual bool		AddProgress(int pProgress=1);
	
	void				Print();
	
	//Is it posted to Game Center / OpenFeint yet?
	bool				mPosted;
	
	//Once mProgress = mProgressMax, we are complete. Great for stuff like "do 5,000 of X."
	int					mProgress;
	int					mProgressMax;
	
	int					mProgressSaved;
	
	//Is the achievement complete?? Well... IS IT?
	bool				mComplete;
	bool				mCompletedThisUpdate;
	
	//Used exclusively for achievement manager...
	bool				mAutoResetsOnLevelUp;
	bool				mAutoResetsOnGameOver;
    
	bool				mAutoResetsOnAction;
	int					mAutoResetsActionId;
};

class FAchievementGroup {
public:
    FAchievementGroup(const char *pGroupName);
    ~FAchievementGroup();

    void                    Add(const char *pAchievementName, int pProgressMax=1);
    void                    AddProgress(FList *pBubbleList, int pProgress=1);
    
    FString                 mGroupName;
    
    FList                   mAchievementList;
};

class FAchievementController {
public:
	FAchievementController();
	~FAchievementController();
    
	void					LevelUp();
	void					GameOver();
	void					PerformAction(int pAction);
	
	void					Reset();
    
    void                    Add(const char *pAchievementName, int pProgressMax=1);
    void                    Add(const char *pAchievementName, const char *pGroupName, int pProgressMax=1);
    
	bool					Exists(FString pName);
    
    void                    GetAllFAchievements(FList *pList);
    
    void                    Synchronize(const char *pAchievementName, int pProgress);
    void                    Synchronize(FAchievement *pAchievement, int pProgress);

    FAchievement            *GetAchievement(const char *pName);
    FAchievement			*GetAchievement(char *pName);
	FAchievement			*GetAchievement(FString pName);
    
    void                    AddProgressGroup(const char *pGroupName, FList *pBubbleList, int pProgress=1);
    FAchievement			*AddProgress(const char *pAchievementName, int pProgress=1);
    
	void					Print();
	
	virtual void			Load();
	virtual void			Save();
    
    FList                   mAchievementList;
    FList                   mFAchievementGroupList;
};


#endif
