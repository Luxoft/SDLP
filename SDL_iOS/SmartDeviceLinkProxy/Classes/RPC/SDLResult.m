//
// Copyright (c) 2013 Ford Motor Company
//

#import "SDLResult.h"

SDLResult* SDLResult_SUCCESS = nil;
SDLResult* SDLResult_INVALID_DATA = nil;
SDLResult* SDLResult_UNSUPPORTED_REQUEST = nil;
SDLResult* SDLResult_OUT_OF_MEMORY = nil;
SDLResult* SDLResult_TOO_MANY_PENDING_REQUESTS = nil;
SDLResult* SDLResult_INVALID_ID = nil;
SDLResult* SDLResult_DUPLICATE_NAME = nil;
SDLResult* SDLResult_TOO_MANY_APPLICATIONS = nil;
SDLResult* SDLResult_APPLICATION_REGISTERED_ALREADY = nil;
SDLResult* SDLResult_UNSUPPORTED_VERSION = nil;
SDLResult* SDLResult_WRONG_LANGUAGE = nil;
SDLResult* SDLResult_APPLICATION_NOT_REGISTERED = nil;
SDLResult* SDLResult_IN_USE = nil;
SDLResult* SDLResult_SUBSCRIBED_ALREADY = nil;
SDLResult* SDLResult_VEHICLE_DATA_NOT_ALLOWED = nil;
SDLResult* SDLResult_VEHICLE_DATA_NOT_AVAILABLE = nil;
SDLResult* SDLResult_REJECTED = nil;
SDLResult* SDLResult_ABORTED = nil;
SDLResult* SDLResult_IGNORED = nil;
SDLResult* SDLResult_UNSUPPORTED_BUTTON = nil;
SDLResult* SDLResult_FILE_NOT_FOUND = nil;
SDLResult* SDLResult_GENERIC_ERROR = nil;

NSMutableArray* SDLResult_values = nil;
@implementation SDLResult

+(SDLResult*) valueOf:(NSString*) value {
    for (SDLResult* item in SDLResult.values) {
        if ([item.value isEqualToString:value]) {
            return item;
        }
    }
    return nil;
}

+(NSMutableArray*) values {
    if (SDLResult_values == nil) {
        SDLResult_values = [[NSMutableArray alloc] initWithObjects:
                SDLResult.SUCCESS,
                SDLResult.INVALID_DATA,
                SDLResult.UNSUPPORTED_REQUEST,
                SDLResult.OUT_OF_MEMORY,
                SDLResult.TOO_MANY_PENDING_REQUESTS,
                SDLResult.INVALID_ID,
                SDLResult.DUPLICATE_NAME,
                SDLResult.TOO_MANY_APPLICATIONS,
                SDLResult.APPLICATION_REGISTERED_ALREADY,
                SDLResult.UNSUPPORTED_VERSION,
                SDLResult.WRONG_LANGUAGE,
                SDLResult.APPLICATION_NOT_REGISTERED,
                SDLResult.IN_USE,
                SDLResult.SUBSCRIBED_ALREADY,
                SDLResult.VEHICLE_DATA_NOT_ALLOWED,
                SDLResult.VEHICLE_DATA_NOT_AVAILABLE,
                SDLResult.REJECTED,
                SDLResult.ABORTED,
                SDLResult.IGNORED,
                SDLResult.UNSUPPORTED_BUTTON,
                SDLResult.FILE_NOT_FOUND,
                SDLResult.GENERIC_ERROR,
                nil];
    }
    return SDLResult_values;
}

+(SDLResult*) SUCCESS {
    	if (SDLResult_SUCCESS == nil) {
        		SDLResult_SUCCESS = [[SDLResult alloc] initWithValue:@"SUCCESS"];
    	}
    	return SDLResult_SUCCESS;
}

+(SDLResult*) INVALID_DATA {
    	if (SDLResult_INVALID_DATA == nil) {
        		SDLResult_INVALID_DATA = [[SDLResult alloc] initWithValue:@"INVALID_DATA"];
    	}
    	return SDLResult_INVALID_DATA;
}

+(SDLResult*) UNSUPPORTED_REQUEST {
    	if (SDLResult_UNSUPPORTED_REQUEST == nil) {
        		SDLResult_UNSUPPORTED_REQUEST = [[SDLResult alloc] initWithValue:@"UNSUPPORTED_REQUEST"];
    	}
    	return SDLResult_UNSUPPORTED_REQUEST;
}

+(SDLResult*) OUT_OF_MEMORY {
    	if (SDLResult_OUT_OF_MEMORY == nil) {
        		SDLResult_OUT_OF_MEMORY = [[SDLResult alloc] initWithValue:@"OUT_OF_MEMORY"];
    	}
    	return SDLResult_OUT_OF_MEMORY;
}

+(SDLResult*) TOO_MANY_PENDING_REQUESTS {
    	if (SDLResult_TOO_MANY_PENDING_REQUESTS == nil) {
        		SDLResult_TOO_MANY_PENDING_REQUESTS = [[SDLResult alloc] initWithValue:@"TOO_MANY_PENDING_REQUESTS"];
    	}
    	return SDLResult_TOO_MANY_PENDING_REQUESTS;
}

+(SDLResult*) INVALID_ID {
    	if (SDLResult_INVALID_ID == nil) {
        		SDLResult_INVALID_ID = [[SDLResult alloc] initWithValue:@"INVALID_ID"];
    	}
    	return SDLResult_INVALID_ID;
}

+(SDLResult*) DUPLICATE_NAME {
    	if (SDLResult_DUPLICATE_NAME == nil) {
        		SDLResult_DUPLICATE_NAME = [[SDLResult alloc] initWithValue:@"DUPLICATE_NAME"];
    	}
    	return SDLResult_DUPLICATE_NAME;
}

+(SDLResult*) TOO_MANY_APPLICATIONS {
    	if (SDLResult_TOO_MANY_APPLICATIONS == nil) {
        		SDLResult_TOO_MANY_APPLICATIONS = [[SDLResult alloc] initWithValue:@"TOO_MANY_APPLICATIONS"];
    	}
    	return SDLResult_TOO_MANY_APPLICATIONS;
}

+(SDLResult*) APPLICATION_REGISTERED_ALREADY {
    	if (SDLResult_APPLICATION_REGISTERED_ALREADY == nil) {
        		SDLResult_APPLICATION_REGISTERED_ALREADY = [[SDLResult alloc] initWithValue:@"APPLICATION_REGISTERED_ALREADY"];
    	}
    	return SDLResult_APPLICATION_REGISTERED_ALREADY;
}

+(SDLResult*) UNSUPPORTED_VERSION {
    	if (SDLResult_UNSUPPORTED_VERSION == nil) {
        		SDLResult_UNSUPPORTED_VERSION = [[SDLResult alloc] initWithValue:@"UNSUPPORTED_VERSION"];
    	}
    	return SDLResult_UNSUPPORTED_VERSION;
}

+(SDLResult*) WRONG_LANGUAGE {
    	if (SDLResult_WRONG_LANGUAGE == nil) {
        		SDLResult_WRONG_LANGUAGE = [[SDLResult alloc] initWithValue:@"WRONG_LANGUAGE"];
    	}
    	return SDLResult_WRONG_LANGUAGE;
}

+(SDLResult*) APPLICATION_NOT_REGISTERED {
    	if (SDLResult_APPLICATION_NOT_REGISTERED == nil) {
        		SDLResult_APPLICATION_NOT_REGISTERED = [[SDLResult alloc] initWithValue:@"APPLICATION_NOT_REGISTERED"];
    	}
    	return SDLResult_APPLICATION_NOT_REGISTERED;
}

+(SDLResult*) IN_USE {
    	if (SDLResult_IN_USE == nil) {
        		SDLResult_IN_USE = [[SDLResult alloc] initWithValue:@"IN_USE"];
    	}
    	return SDLResult_IN_USE;
}

+(SDLResult*) SUBSCRIBED_ALREADY {
    	if (SDLResult_SUBSCRIBED_ALREADY == nil) {
        		SDLResult_SUBSCRIBED_ALREADY = [[SDLResult alloc] initWithValue:@"SUBSCRIBED_ALREADY"];
    	}
    	return SDLResult_SUBSCRIBED_ALREADY;
}

+(SDLResult*) VEHICLE_DATA_NOT_ALLOWED {
    	if (SDLResult_VEHICLE_DATA_NOT_ALLOWED == nil) {
        		SDLResult_VEHICLE_DATA_NOT_ALLOWED = [[SDLResult alloc] initWithValue:@"VEHICLE_DATA_NOT_ALLOWED"];
    	}
    	return SDLResult_VEHICLE_DATA_NOT_ALLOWED;
}

+(SDLResult*) VEHICLE_DATA_NOT_AVAILABLE {
    	if (SDLResult_VEHICLE_DATA_NOT_AVAILABLE == nil) {
        		SDLResult_VEHICLE_DATA_NOT_AVAILABLE = [[SDLResult alloc] initWithValue:@"VEHICLE_DATA_NOT_AVAILABLE"];
    	}
    	return SDLResult_VEHICLE_DATA_NOT_AVAILABLE;
}

+(SDLResult*) REJECTED {
    	if (SDLResult_REJECTED == nil) {
        		SDLResult_REJECTED = [[SDLResult alloc] initWithValue:@"REJECTED"];
    	}
    	return SDLResult_REJECTED;
}

+(SDLResult*) ABORTED {
    	if (SDLResult_ABORTED == nil) {
        		SDLResult_ABORTED = [[SDLResult alloc] initWithValue:@"ABORTED"];
    	}
    	return SDLResult_ABORTED;
}

+(SDLResult*) IGNORED {
    	if (SDLResult_IGNORED == nil) {
        		SDLResult_IGNORED = [[SDLResult alloc] initWithValue:@"IGNORED"];
    	}
    	return SDLResult_IGNORED;
}

+(SDLResult*) UNSUPPORTED_BUTTON {
    	if (SDLResult_UNSUPPORTED_BUTTON == nil) {
        		SDLResult_UNSUPPORTED_BUTTON = [[SDLResult alloc] initWithValue:@"UNSUPPORTED_BUTTON"];
    	}
    	return SDLResult_UNSUPPORTED_BUTTON;
}

+(SDLResult*) FILE_NOT_FOUND {
    	if (SDLResult_FILE_NOT_FOUND == nil) {
        		SDLResult_FILE_NOT_FOUND = [[SDLResult alloc] initWithValue:@"FILE_NOT_FOUND"];
    	}
    	return SDLResult_FILE_NOT_FOUND;
}

+(SDLResult*) GENERIC_ERROR {
    	if (SDLResult_GENERIC_ERROR == nil) {
        		SDLResult_GENERIC_ERROR = [[SDLResult alloc] initWithValue:@"GENERIC_ERROR"];
    	}
    	return SDLResult_GENERIC_ERROR;
}

@end
