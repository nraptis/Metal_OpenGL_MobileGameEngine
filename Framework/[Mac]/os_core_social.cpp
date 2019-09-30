//
//  core_social.cpp
//  2015 Gnome Launcher
//
//  Created by Nick Raptis on 11/22/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "os_core_social.h"
#include "os_core_outlets.h"

#include "FString.hpp"

bool cFacebookLoggedIn = false;
bool cFacebookLoggingIn = false;
bool cFacebookLogInError = false;

bool cFacebookConnecting = false;



bool cFacebookPermissionEmail = false;
bool cFacebookPermissionOfflineAccess = false;
bool cFacebookPermissionPublishActions = false;
bool cFacebookPermissionUserAboutMe = false;
bool cFacebookPermissionUserPhotos = false;
bool cFacebookPermissionUserFriends = false;
bool cFacebookPermissionUserGamesActivity = false;


//offline_access
//publish_actions
//user_about_me
//user_photos
//user_location
//user_friends
//user_games_activity

FString cFacebookToken;
FString cFacebookName;




void social_Init()
{
    cFacebookLoggedIn = false;
    cFacebookLoggingIn = false;
    cFacebookLogInError = false;
    
    cFacebookConnecting = false;
    
    cFacebookPermissionEmail = false;
    cFacebookPermissionOfflineAccess = false;
    cFacebookPermissionPublishActions = false;
    cFacebookPermissionUserAboutMe = false;
    cFacebookPermissionUserPhotos = false;
    cFacebookPermissionUserFriends = false;
    cFacebookPermissionUserGamesActivity = false;
    
    cFacebookToken = "";
    cFacebookName = "";
}

void social_FacebookLogIn()
{
    //Log("social_FacebookLogIn(Logged %d  Logging %d)!\n", cFacebookLoggedIn, cFacebookLoggingIn);
    
    if((cFacebookLoggingIn == true) || (cFacebookConnecting == true))
    {
        return;
    }
    
    /*
     cFacebookConnecting = true;
     cFacebookLoggingIn = true;
     cFacebookLogInError = false;
     */
    
}

void social_FacebookLogOut()
{
    
}

bool social_FacebookLogInDidComplete()
{
    bool aResult = false;
    
    
    return aResult;
}

bool social_FacebookLogInDidSucceed()
{
    bool aResult = false;
    
    
    return aResult;
}

bool social_FacebookLogInDidFail()
{
    bool aResult = false;
    
    
    return aResult;
}

bool social_FacebookIsBusy()
{
    bool aResult = false;
    
    
    return aResult;
}

bool social_FacebookIsLoggingIn()
{
    bool aResult = false;
    
    
    return aResult;
}

bool social_FacebookIsLoggedIn()
{
    bool aResult = false;
    
    
    return aResult;
}

char *social_FacebookGetName()
{
    char *aResult = 0;
    
    
    return aResult;
}

char *social_FacebookGetEmail()
{
    char *aResult = 0;
    
    
    return aResult;
}

char *social_FacebookGetAccessToken()
{
    char *aResult = 0;
    
    
    return aResult;
}

void social_FacebookPullFriends()
{
    
}
























