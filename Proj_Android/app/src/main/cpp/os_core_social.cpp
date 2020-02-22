//
//  core_social.cpp
//  2015 Fleet XP
//
//  Created by Nick Raptis on 11/22/14.
//  Copyright (c) 2014 Applejacks Microsoft Cloud Wizzywig Pippy Longstocking. All rights reserved.
//

#include "os_core_social.h"
#include "os_core_outlets.h"
//#import <FBSDKCoreKit/FBSDKCoreKit.h>
//#import <FBSDKLoginKit/FBSDKLoginKit.h>
//#import <FBSDKMessengerShareKit/FBSDKMessengerShareKit.h>
//#import <FBSDKShareKit/FBSDKShareKit.h>

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
    /*
    Log("social_FacebookLogIn(Logged %d  Logging %d)!\n", cFacebookLoggedIn, cFacebookLoggingIn);
    
    if((cFacebookLoggingIn == true) || (cFacebookConnecting == true))
    {
        return;
    }
    
    cFacebookConnecting = true;
    
    cFacebookLoggingIn = true;
    cFacebookLogInError = false;
    
    //[FBSDK set]
    
    //393938300660912
    //393938300660912
    
    //offline_access
    //publish_actions
    //user_about_me
    //user_photos
    //user_location
    //user_friends
    //user_games_activity
    
    NSMutableArray *aPermissionsArray = [[NSMutableArray alloc] init];
    
    [aPermissionsArray addObject:@"email"];
    //[aPermissionsArray addObject:@"offline_access"];
    //[aPermissionsArray addObject:@"publish_actions"];
    [aPermissionsArray addObject:@"user_about_me"];
    [aPermissionsArray addObject:@"user_friends"];
    
    FBSDKLoginManager *aLoginManager = [[FBSDKLoginManager alloc] init];
    [aLoginManager logInWithReadPermissions:aPermissionsArray//@[@"email"]
                            handler:^(FBSDKLoginManagerLoginResult *pResult, NSError *pError)
    {
        //aLoginManager
        
        cFacebookConnecting = false;
        cFacebookLoggingIn = false;
        
        if(pError != nil)
        {
            
            
            cFacebookLogInError = true;
            
            Log("social_FacebookLogIn(ERROR)!\n");
            NSLog(@"Err[%@]", [pError description]);
     // Process error
        }
        else
        {
            if(pResult.token)
            {
                NSString *aTokenString = [pResult.token tokenString];
                if(aTokenString)
                {
                    cFacebookToken = [aTokenString UTF8String];
                    Log("Facebook Token[%s]\n\n", cFacebookToken.c());
                }
            }
            
            cFacebookLogInError = false;
            
            if(pResult.isCancelled)
            {
                Log("social_FacebookLogIn(CANCELLED)!\n");
            }
            else
            {
                Log("social_FacebookLogIn(NOT CANCELLED)!\n");
            }
            
            NSLog(@"%@", pResult.grantedPermissions);
            
            if([pResult.grantedPermissions containsObject:@"email"])cFacebookPermissionEmail = true;
            else cFacebookPermissionEmail = false;
            
            if([pResult.grantedPermissions containsObject:@"offline_access"])cFacebookPermissionOfflineAccess = true;
            else cFacebookPermissionOfflineAccess = false;
            
            if([pResult.grantedPermissions containsObject:@"publish_actions"])cFacebookPermissionPublishActions = true;
            else cFacebookPermissionPublishActions = false;
            
            if([pResult.grantedPermissions containsObject:@"user_about_me"])cFacebookPermissionUserAboutMe = true;
            else cFacebookPermissionUserAboutMe = false;
            
            if([pResult.grantedPermissions containsObject:@"user_photos"])cFacebookPermissionUserPhotos = true;
            else cFacebookPermissionUserPhotos = false;
            
            if([pResult.grantedPermissions containsObject:@"user_friends"])cFacebookPermissionUserFriends = true;
            else cFacebookPermissionUserFriends = false;
            
            if([pResult.grantedPermissions containsObject:@"user_games_activity"])cFacebookPermissionUserGamesActivity = true;
            else cFacebookPermissionUserGamesActivity = false;
            
            Log("Allowed Permissions = [");
            if(cFacebookPermissionEmail)Log("email ");
            if(cFacebookPermissionOfflineAccess)Log("offline_access ");
            if(cFacebookPermissionPublishActions)Log("publish_actions ");
            if(cFacebookPermissionUserAboutMe)Log("user_about_me ");
            if(cFacebookPermissionUserPhotos)Log("user_photos ");
            if(cFacebookPermissionUserFriends)Log("user_friends ");
            if(cFacebookPermissionUserGamesActivity)Log("user_games_activity ");
            Log("]\n");
            
            Log("Denied Permissions = [");
            if(cFacebookPermissionEmail == false)Log("email ");
            if(cFacebookPermissionOfflineAccess == false)Log("offline_access ");
            if(cFacebookPermissionPublishActions == false)Log("publish_actions ");
            if(cFacebookPermissionUserAboutMe == false)Log("user_about_me ");
            if(cFacebookPermissionUserPhotos == false)Log("user_photos ");
            if(cFacebookPermissionUserFriends == false)Log("user_friends ");
            if(cFacebookPermissionUserGamesActivity == false)Log("user_games_activity ");
            Log("]\n");
            
            //pResult.
            
        }
    }];
    
    */
}

void social_FacebookLogOut()
{
    
}

bool social_FacebookLogInDidComplete()
{
    bool aReturn = false;
    
    
    return aReturn;
}

bool social_FacebookLogInDidSucceed()
{
    bool aReturn = false;
    
    
    return aReturn;
}

bool social_FacebookLogInDidFail()
{
    bool aReturn = false;
    
    
    return aReturn;
}

bool social_FacebookIsBusy()
{
    bool aReturn = false;
    
    
    return aReturn;
}

bool social_FacebookIsLoggingIn()
{
    bool aReturn = false;
    
    
    return aReturn;
}

bool social_FacebookIsLoggedIn()
{
    bool aReturn = false;
    
    
    return aReturn;
}

char *social_FacebookGetName()
{
    char *aReturn = 0;
    
    
    return aReturn;
}

char *social_FacebookGetEmail()
{
    char *aReturn = 0;
    
    
    return aReturn;
}

char *social_FacebookGetAccessToken()
{
    char *aReturn = 0;
    
    
    return aReturn;
}

void social_FacebookPullFriends()
{
    /*
    
    NSMutableString *facebookRequest = [NSMutableString new];
    [facebookRequest appendString:@"/me/friends"];
    //[facebookRequest appendString:@"me/friendlists"];
    //[facebookRequest appendString:@"/{friend-list-id}/members"];
    
    [facebookRequest appendString:@"?limit=100"];
    [facebookRequest appendString:@"&fields=name,picture"];
    //[facebookRequest appendString:@"&fields=name,picture,gender"];
    
    
    //FBSDKGraphRequest *request = [[FBSDKGraphRequest alloc] initWithGraphPath:facebookRequest parameters:nil HTTPMethod:@"GET"];
    
    //[request startWithCompletionHandler:<YOUR BLOCK HERE>];
    //requestForGraphPath:@"me/friends?fields=name,picture,gender"];
    
    
    // For more complex open graph stories, use `FBSDKShareAPI`
    // with `FBSDKShareOpenGraphContent`

    FBSDKGraphRequest *request = [[FBSDKGraphRequest alloc] initWithGraphPath: facebookRequest   //@"/{user-id}/friendlists"
                                  parameters:nil
                                  HTTPMethod:@"GET"];
    [request startWithCompletionHandler:^(FBSDKGraphRequestConnection *connection,
                                          id result,
                                          NSError *error)
    {
        
        NSLog(@"Friend Results = [%@]\n\n", result);
        
        // Handle the result
    }];
    
    
    
    //pictureURL =  [NSString stringWithFormat:@"https://graph.facebook.com/%@/picture?width=50&height=50", [data objectForKey:@"id"]];
    
    //https://graph.facebook.com/me/friends?access_token=[oauth_token]&fields=name,id,picture
    */
    
    /*
    
    //NSLog(@"permissions::%@",FBSession.activeSession.permissions);
    
    // if the session is closed, then we open it here, and establish a handler for state changes
    [FBSession openActiveSessionWithReadPermissions:@[@"basic_info", @"user_friends"]
                                       allowLoginUI:YES
                                  completionHandler:^(FBSession *session,
                                                      FBSessionState state,
                                                      NSError *error) {
                                      if (error)
                                      {
                                          UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Error"
                                                                                              message:error.localizedDescription
                                                                                             delegate:nil
                                                                                    cancelButtonTitle:@"OK"
                                                                                    otherButtonTitles:nil];
                                          [alertView show];
                                      }
                                      else if (session.isOpen)
                                      {
                                          [self showWithStatus:@""];
                                          FBRequest *friendRequest = [FBRequest requestForGraphPath:@"me/friends?fields=name,picture,gender"];
                                          
                                          
                                          [friendRequest startWithCompletionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
                                              NSArray *data = [result objectForKey:@"data"];
                                              NSMutableArray *friendsList = [[NSMutableArray alloc] init];
                                              for (FBGraphObject<FBGraphUser> *friend in data)
                                              {
                                                  //NSLog(@"friend:%@", friend);
                                                  NSDictionary *picture = [friend objectForKey:@"picture"];
                                                  NSDictionary *pictureData = [picture objectForKey:@"data"];
                                                  //NSLog(@"picture:%@", picture);
                                                  FBData *fb = [[FBData alloc]
                                                                initWithData:(NSString*)[friend objectForKey:@"name"]
                                                                userID:(NSInteger)[[friend objectForKey:@"id"] integerValue]
                                                                gender:(NSString*)[friend objectForKey:@"gender"]
                                                                photoURL:(NSString*)[pictureData objectForKey:@"url"]
                                                                photo:(UIImage*)nil
                                                                isPhotoDownloaded:(BOOL)NO];
                                                  [friendsList addObject:fb];
                                              }
                                              
                                              [self dismissStatus];
                                              if (completed) {
                                                  completed(friendsList,@"I got it");
                                              }
                                          }];
                                          
                                          
                                      }
                                  }];
}     
*/
    
}

/*
FBRequest *friendRequest = [FBRequest requestForGraphPath:@"me/friends?fields=name,picture,birthday,location"];
[ friendRequest startWithCompletionHandler:^(FBRequestConnection *connection, id result, NSError *error) {
    NSArray *data = [result objectForKey:@"data"];
    for (FBGraphObject<FBGraphUser> *friend in data) {
        NSLog(@"%@:%@", [friend name],[friend birthday]);
    }}];
*/

















