//
//  core_social.h
//  2015 Gnome Launcher
//
//  Created by Nick Raptis on 11/22/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef ___015_Fleet_XP__core_social__
#define ___015_Fleet_XP__core_social__

void                            social_Init();

void                            social_FacebookLogIn();
void                            social_FacebookLogOut();

bool                            social_FacebookLogInDidComplete();
bool                            social_FacebookLogInDidSucceed();
bool                            social_FacebookLogInDidFail();

bool                            social_FacebookIsBusy();
bool                            social_FacebookIsLoggingIn();
bool                            social_FacebookIsLoggedIn();

void                            social_FacebookPullFriends();


char                            *social_FacebookGetName();
char                            *social_FacebookGetEmail();
char                            *social_FacebookGetAccessToken();



//void                            social_FacebookGet();





#endif /* defined(___015_Fleet_XP__core_social__) */
