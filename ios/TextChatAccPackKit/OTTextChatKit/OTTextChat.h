//
//  OTTextChat.h
//
//  Copyright © 2016 Tokbox, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OTTextChatKit/OTTextMessage.h>

/**
 *  @typedef  TextChatViewEventSignal                  NS_ENUM for the signal generated by the text chat.
 *  @brief    this enum describes the types for event signals send by the text chat
 *  @constant TextChatViewEventSignalDidSendMessage    The component sent a message.
 *  @constant TextChatViewEventSignalDidReceiveMessage The component received a new message.
 *  @constant TextChatViewEventSignalDidConnect        A disconnect was requested and succeeded.
 *  @constant TextChatViewEventSignalDidDisconnect     A new connection was requested and succeeded.
 */
typedef NS_ENUM(NSUInteger, OTTextChatConnectionEventSignal) {
    OTTextChatConnectionEventSignalDidConnect = 0,
    OTTextChatConnectionEventSignalDidDisconnect,
    OTTextChatConnectionEventSignalConnectionCreated,
    OTTextChatConnectionEventSignalConnectionDestroyed
};

typedef NS_ENUM(NSUInteger, OTTextChatMessageEventSignal) {
    OTTextChatMessageEventSignalDidSendMessage = 0,
    OTTextChatMessageEventSignalDidReceiveMessage
};

@class OTTextChat;
@class OTTextChatConnection;
@class OTTextChatViewController;

/**
 *  TextChatEventBlock type for the various connection signals.
 *
 *  @param signal       NS_ENUM send with one of the signal defined for TextChatEventSignal.
 *  @param connection   The connection created or destroyed.
 *  @param error        The error object indicating there is a problem when sending the signal.
 */
typedef void (^OTTextChatConnectionBlock)(OTTextChatConnectionEventSignal signal, OTTextChatConnection *connection, NSError *);

/**
 *  TextChatEventBlock type for the various text message signals.
 *
 *  @param signal       NS_ENUM send with one of the signal defined for TextChatEventSignal.
 *  @param textMessage  The current message sent or received.
 *  @param error        The error object indicating there is a problem when sending the signal.
 */
typedef void (^OTTextChatMessageBlock)(OTTextChatMessageEventSignal signal, OTTextMessage *textMessage, NSError *);

/**
 *  The delegate of a TextChatView object must confirm to the TextChatViewDelegate protocol.
 *  Optional methods of the protocol allow the delegate to notify the connectivity.
 */
@protocol OTTextChatViewDelegate <NSObject>

@optional
/**
 *  Notifies the delegate that the text chat view finished sending the message, with or without an error.
 *
 *  @param textChat     The text chat component object.
 *  @param textMessage  The text message object.
 *  @param error        An error object, used by the text chat view, when there is an error sending a message.
 */
- (void)textChat:(OTTextChat *)textChat didSendTextMessage:(OTTextMessage *)textMessage error:(NSError *)error;

/**
 *  Notifies the delegate that the text chat view finished receiving the message, with or without an error.
 *
 *  @param textChat     The text chat component object.
 *  @param textMessage  The text message object.
 *  @param error        An error object, used by the text chat view, when there is an error receiving a message.
 */
- (void)textChat:(OTTextChat *)textChat didReceiveTextMessage:(OTTextMessage *)textMessage error:(NSError *)error;

/**
 *  Notifies the delegate the text chat view has established a text chat connection, with or without an error.
 *
 *  @param textChat The text chat component object.
 *  @param error    An error object. It can contain information related to a connection error, a nil value,
 *               or information indicating a successful connection.
 */
- (void)textChat:(OTTextChat *)textChat didConnectWithError:(NSError *)error;

/**
 *  Notifies the delegate that the text chat view has stopped a text chat connection, with or without an error.
 *
 *  @param textChat The text chat component object.
 *  @param error    An error object. It can contain information related to a disconnect error, a nil value,
 *               or information indicating a connection was successfully closed.
 */
- (void)textChat:(OTTextChat *)textChat didDisConnectWithError:(NSError *)error;

- (void)textChat:(OTTextChat *)textChat connectionCreated:(OTTextChatConnection *)connection;

- (void)textChat:(OTTextChat *)textChat connectionDestroyed:(OTTextChatConnection *)connection;

@end

@interface OTTextChatConnection : NSObject

/**
 * The unique connection ID for this OTConnection object.
 */
@property(readonly) NSString* connectionId;

/**
 * The time at which the Connection was created on the OpenTok server.
 */
@property(readonly) NSDate* creationTime;

/**
 * A string containing metadata describing the connection. You can add this
 * connection data when you
 * [create a token](https://tokbox.com/developer/guides/create-token/).
 */
@property(readonly) NSString* customdData;

@end

@interface OTTextChat : NSObject

/**
 *  Add the configuration detail to your app.
 *
 *  @param apiKey       Your OpenTok API key.
 *  @param sessionId    The session ID of this instance.
 *  @param token        The token generated for this connection.
 */
+ (void)setOpenTokApiKey:(NSString *)apiKey
               sessionId:(NSString *)sessionId
                   token:(NSString *)token;

/**
 *  The object that acts as the delegate of the text chat view.
 *
 *  The delegate must adopt the TextChatViewDelegate protocol. The delegate is not retained.
 */
@property (weak, nonatomic) id<OTTextChatViewDelegate> delegate;

/**
 *  @return Returns an initialized text chat view object.
 */
+ (instancetype)textChat;

/**
 *  Establishes a text chat connection.
 */
- (void)connect;

/**
 *  Establishes a text chat connection with completion.
 *
 *  @param handler NS_ENUM for the various event signals.
 */
- (void)connectWithHandler:(OTTextChatConnectionBlock)handler;

/**
 *  Stops a text chat connection.
 */
- (void)disconnect;

@property (nonatomic) NSString *alias;

@property (readonly, nonatomic) NSString *receiverAlias;

@property (readonly, nonatomic) OTTextChatConnection *selfConnection;

@property (copy, nonatomic) OTTextChatConnectionBlock connectionHandler;

@property (copy, nonatomic) OTTextChatMessageBlock messageHandler;

- (void)sendMessage:(NSString *)text;

- (void)sendCustomMessage:(OTTextMessage *)textMessage;

@end
