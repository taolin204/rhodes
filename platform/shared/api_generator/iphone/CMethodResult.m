
#import "CMethodResult.h"

#import "CRubyConverter.h"
#import "CJSConverter.h"
#import "RubyCallbackHelper.h"


@implementation CMethodResultError

-(id)init:(NSString*)error_type description:(NSString*)description {
    self = [super init];
    errorType = error_type;
    errorDescription = description;
    return self;
}

+ (CMethodResultError*) errorWithType:(NSString*)error_type description:(NSString*)description {
    CMethodResultError* b = [[CMethodResultError alloc] init:error_type description:description];
    return b;
}

-(NSString*)getErrorType {
    return errorType;
}

-(NSString*)getErrorDescription {
    return errorDescription;
}

-(void)dealloc {
    [errorDescription release];
    [super dealloc];
}


@end


@implementation CRhoAPIClassInstance

- (id) init:(NSString*)clasRubyFullName iID:(NSString*)iID {
    self = [super init];
    mClassName = [clasRubyFullName retain];
    mInstanceID = [iID retain];
    return self;
}

+(CRhoAPIClassInstance*) rubyClassByName:(NSString*)className instanceID:(NSString*)instanceID {
    CRhoAPIClassInstance* m = [[CRhoAPIClassInstance alloc] init:className iID:instanceID];
    return m;
}

-(NSString*)getClassName {
    return mClassName;
}

-(NSString*)getInstanceID {
    return mInstanceID;
}

-(void)dealloc {
    [mClassName release];
    [mInstanceID release];
    [super dealloc];
}

@end





@implementation CMethodResult

-(id) init {
    self = [super init];
    mValue = nil;
    mRubyCallbackURL = nil;
    mJSCallbackUID = nil;
    mCallbackParam = nil;
    mRubyFactory = nil;
    mRubyModulePath = nil;
    return self;
}

- (void) setResult:(NSObject*)value {
    if (mRubyModulePath != nil) {
        // convert all strings into CRubyModule !
        if ([value isKindOfClass:[NSString class]]) {
            mValue = [CRhoAPIClassInstance rubyClassByName:mRubyModulePath instanceID:((NSString*)value)];
        }
        else if ([value isKindOfClass:[NSArray class]]) {
            NSArray* value_ar = (NSArray*)value;
            NSMutableArray* aValue = [NSMutableArray arrayWithCapacity:[value_ar count]];
            int i;
            for (i = 0; i < [value_ar count]; i++) {
                NSObject* item = [value_ar objectAtIndex:i];
                if ([item isKindOfClass:[NSString class]]) {
                    item = [CRhoAPIClassInstance rubyClassByName:mRubyModulePath instanceID:((NSString*)item)];
                }
                [aValue addObject:item];
            }
            mValue = aValue;
        }
        else {
            mValue = [value retain];
        }
    }
    else {
        mValue = [value retain];
    }
    [self callCallback];
}

-(NSObject*) getResult {
    return mValue;
}


-(VALUE) toRuby {
    if (mRubyFactory != nil) {
        return [mRubyFactory makeRubyValue:mValue];
    }
    return [CRubyConverter convertToRuby:mValue];
}

-(NSString*) toJSON {
    NSString* res = [CJSConverter convertToJS:mValue level:0];
    const char* ttt = [res UTF8String];
    return res;
}

-(BOOL) isHash {
    return [mValue isKindOfClass:[NSDictionary class]];
}

-(NSDictionary*) getHashResult {
    return (NSDictionary*)mValue;
}


-(void) setRubyCallback:(NSString*)url {
    mRubyCallbackURL = [url retain];
}

-(void) setJSCallback:(NSString*)uid {
    mJSCallbackUID = [uid retain];
}

-(void) setCallbackParam:(NSString*)param {
    mCallbackParam = [param retain];
}

-(void) callRubyCallback:(NSString*)url {
    RubyCallbackHelper_callCallback(mRubyCallbackURL, self, mCallbackParam);
}

-(void) setRubyFactory:(id<IMethodResult_RubyObjectFactory>)factory {
    mRubyFactory = factory;
}

-(void) enableObjectCreationModeWithRubyClassPath:(NSString*)classPath {
    mRubyModulePath = [classPath stringByReplacingOccurrencesOfString:@"." withString:@"::"];
}



-(void) callJSCallback:(NSString*)uid {
    //TODO:
}

-(void) callCallback {
    if (mRubyCallbackURL != nil) {
        [self callRubyCallback:mRubyCallbackURL];
    }
    else if (mJSCallbackUID != nil) {
        [self callJSCallback:mJSCallbackUID];
    }
}

+ (NSObject*) getObjectiveCNULL {
    return [NSNull null];
}


+ (BOOL)isBoolInsideNumber:(NSNumber*)number {
    return [number objCType][0] == 'c';
}

+ (BOOL)isFloatInsideNumber:(NSNumber*)number {
    return ([number objCType][0] == 'f') || ([number objCType][0] == 'd');
}

+ (BOOL)isIntInsideNumber:(NSNumber*)number {
    return [number objCType][0] == 'i';
}




-(void) dealloc {
    [mRubyCallbackURL release];
    [mJSCallbackUID release];
    [mCallbackParam release];
    [mValue release];
    [mRubyModulePath release];
    [super dealloc];
}


@end
