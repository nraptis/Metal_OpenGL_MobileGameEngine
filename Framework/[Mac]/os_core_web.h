//
//  os_core_web.h
//  2015 Gnome Launcher
//
//  Created by Nick Raptis on 11/22/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef ___015_Fleet_XP__os_core_web__
#define ___015_Fleet_XP__os_core_web__

void                            os_web_Update();

void                            os_web_HTTPRequestMake(const char *pURL, int pRequestID);

bool                            os_web_HTTPRequestDidComplete(int pRequestID);
bool                            os_web_HTTPRequestDidFail(int pRequestID);
bool                            os_web_HTTPRequestDidSucceed(int pRequestID);

char                            *os_web_HTTPRequestData(int pRequestID);

void                            os_web_HTTPRequestPurge(int pRequestID);





#endif /* defined(___015_Fleet_XP__os_core_web__) */
