//
//  OSStoreManager.h
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 10/19/20.
//  Copyright © 2020 Froggy Studios. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

@interface OSStoreManager : NSObject <SKPaymentTransactionObserver, SKProductsRequestDelegate, SKRequestDelegate>

@property (nonatomic, retain) SKProductsRequest *productRequest;
@property (nonatomic, assign) BOOL restoring;
@property (nonatomic, retain) NSString *productIdentifier;


//First call this.
- (id) init;

- (void) purchaseProduct: (NSString *)productIdentifier;

- (void) restorePurchases;



//SKRequestDelegate

- (void) requestDidFinish: (SKRequest *)request;
- (void) request:(SKRequest *)request didFailWithError: (NSError *)error;


//SKProductsRequestDelegate

- (void) productsRequest: (SKProductsRequest *)request didReceiveResponse: (SKProductsResponse *)response;



//SKPaymentTransactionObserver

// Sent when the transaction array has changed (additions or state changes).  Client should check state of transactions and finish as appropriate.
- (void) paymentQueue: (SKPaymentQueue *)queue updatedTransactions: (NSArray<SKPaymentTransaction *> *)transactions;

- (void) paymentQueue: (SKPaymentQueue *)queue removedTransactions: (NSArray<SKPaymentTransaction *> *)transactions;

// Sent when an error is encountered while adding transactions from the user's purchase history back to the queue.
- (void) paymentQueue: (SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError: (NSError *)error;

// Sent when all transactions from the user's purchase history have successfully been added back to the queue.
- (void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentQueue *)queue;

// Sent when the download state has changed.
- (void) paymentQueue: (SKPaymentQueue *)queue updatedDownloads: (NSArray<SKDownload *> *)downloads;

@end




/*
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

@interface OSMusicPlayer : NSObject <AVAudioPlayerDelegate> {
    AVAudioPlayer                           *musicPlayer;
    AVAudioPlayer                           *musicPlayerFading;
    
    int                                     musicFadeOutTick;
    int                                     musicFadeOutTickMax;
    bool                                    musicFadeOut;
    
    int                                     musicFadeInTick;
    int                                     musicFadeInTickMax;
    bool                                    musicFadeIn;
    
    
    float                                   musicVolume;
    
    bool                                    musicLoop;
    bool                                    musicFadeLoop;
}

@property (nonatomic, strong) AVAudioPlayer *musicPlayer;
@property (nonatomic, strong) AVAudioPlayer *musicPlayerFading;

- (id)init;

- (void)updateFade;

- (void)musicPlay:(NSString *)pFilePath withLoop:(BOOL)pLoop;
- (void)musicPlay:(NSString *)pFilePath withVolume:(float)pVolume withLoop:(BOOL)pLoop;

- (void)musicCrossFadeWithPath:(NSString *)pFilePath withDurationTicks:(int)pDurationTicks withLoop:(BOOL)pLoop;
 

@end

*/

/*

import UIKit
import StoreKit
 
class StoreManager: NSObject, SKProductsRequestDelegate, SKPaymentTransactionObserver, URLSessionDelegate, SKRequestDelegate {
    
    //StoreManager.bounceSubscriptionID
    
    static let bounceSubscriptionID = "bounce_deluxe"
    static let jigglePurchaseID = "jiggle_2_deluxe"
    
    static let shared = StoreManager()
    
    private override init() {
        super.init()
        //SKPaymentQueue.default().add(self)
    }
    
    static func getProductID()-> String {
        if ApplicationController.jiggle {
            return StoreManager.jigglePurchaseID
        } else {
            return StoreManager.bounceSubscriptionID
        }
    }
    
    private var _isActive: Bool = false
    private var _isPurchasing: Bool = false
    private var _isRestoring: Bool = false
    
    var isActive: Bool { return _isActive }
    var isPurchasing: Bool { return _isActive && _isPurchasing }
    var isRestoring: Bool { return _isActive && _isRestoring }
    
    //var productID: String = ""
    var sharedSecret: String = ""
    
    var productsRequest: SKProductsRequest?
    var products = [String: SKProduct]()
    
    func bounceStartSubscriptionPurchase() {
        
        EventLogger.shared.logEvent(type: "Subscription", name: "StartSubscription")
        
        _isActive = true
        _isPurchasing = true
        _isRestoring = false
        
 @property (nonatomic, retain) SKProductsRequest *productRequest;

        if let oldRequest = productsRequest {
            //If the old request is still alive, kill it
            oldRequest.cancel()
            oldRequest.delegate = nil
            productsRequest = nil
        }
        
        StoreManager.postNotification(.purchaseBegin)
        
        print("Starting Purchase [\(StoreManager.bounceSubscriptionID)]")
        
        productsRequest = SKProductsRequest(productIdentifiers: [StoreManager.bounceSubscriptionID])
        productsRequest!.delegate = self
        productsRequest!.start()
    }
    
    func jiggleStartPurchase() {
        
        EventLogger.shared.logEvent(type: "Purchase", name: "StartPurchase")
        
        _isActive = true
        _isPurchasing = true
        _isRestoring = false
        
        if let oldRequest = productsRequest {
            //If the old request is still alive, kill it
            oldRequest.cancel()
            oldRequest.delegate = nil
            productsRequest = nil
        }
        
        StoreManager.postNotification(.purchaseBegin)
        
        print("Starting Purchase [\(StoreManager.jigglePurchaseID)]")
        
        productsRequest = SKProductsRequest(productIdentifiers: [StoreManager.jigglePurchaseID])
        productsRequest!.delegate = self
        productsRequest!.start()
    }
    
    func restorePurchases() {
        EventLogger.shared.logEvent(type: "Subscription", name: "StartRestoreSubscription")
        
        _isActive = true
        _isPurchasing = false
        _isRestoring = true
        
        SKPaymentQueue.default().restoreCompletedTransactions()
    }
    
    fileprivate func purchaseSucceed() {
        EventLogger.shared.logEvent(type: "Subscription", name: "PurchaseSucceed")
        
        _isActive = false
        _isPurchasing = false
        _isRestoring = false
        
        StoreManager.postNotification(.purchaseSuccess)
    }
    
    fileprivate func restoreSucceed() {
        EventLogger.shared.logEvent(type: "Subscription", name: "RestoreSucceed")
        
        _isActive = false
        _isPurchasing = false
        _isRestoring = false
        
        StoreManager.postNotification(.restoreSuccess)
    }
    
    fileprivate func restoreFail() {
        EventLogger.shared.logEvent(type: "Subscription", name: "RestoreFail")
        
        _isActive = false
        _isPurchasing = false
        _isRestoring = false
        
        if let oldRequest = productsRequest {
            oldRequest.cancel()
            oldRequest.delegate = nil
            productsRequest = nil
        }
        
        StoreManager.postNotification(.restoreFail)
    }
    
    internal func fail() {
        _isActive = false
        _isPurchasing = false
        _isRestoring = false
        
        if let oldRequest = productsRequest {
            oldRequest.cancel()
            oldRequest.delegate = nil
            productsRequest = nil
        }
        
        StoreManager.postNotification(.purchaseFail)
        
        self.processReceiptIfNew()
    }
    
    public func requestDidFinish(_ request: SKRequest) {
        print("request \(request)")
        print("requestDidFinish")
        //if FileUtils.loadFileData(Bundle.main.appStoreReceiptURL?.path) != nil {
        //    processReceipt()
        //}
    }
       
    public func request(_ request: SKRequest, didFailWithError error: Error) {
        print("request \(request)")
        print("didFailWithError \(error.localizedDescription)")
    }
    
    // MARK: SKProductsRequestDelegate
    func productsRequest(_ request: SKProductsRequest, didReceive response: SKProductsResponse) {
        
        var index: Int = 0
        for product in response.products {
            products[product.productIdentifier] = product
            index += 1
        }
        
        if SKPaymentQueue.canMakePayments() {
            print("canMakePayments = true")
            let productID = StoreManager.getProductID()
            if let product: SKProduct = products[productID] {
                print("does have product = true")
                let payment = SKPayment(product: product)
                SKPaymentQueue.default().add(payment)
            } else {
                print("no product id?")
                fail()
            }
        } else {
            print("canMakePayments = false")
            fail()
        }
    }
    
    //MARK: SKPaymentTransactionObserver
    func paymentQueue(_ queue: SKPaymentQueue, updatedTransactions transactions: [SKPaymentTransaction]) {
        
        print("Update Transaction")
        for transaction in transactions {
            
            if let error = transaction.error {
                print("Failed Error: \(error.localizedDescription)")
            }
            
            switch transaction.transactionState {
            case SKPaymentTransactionState.purchased:
                print("---- Transaction => Purchased")
                SKPaymentQueue.default().finishTransaction(transaction)
                performOnMainQueue {
                    self.purchaseSucceed()
                    if ApplicationController.jiggle {
                        Config.shared.notifyJigglePurchased()
                    } else {
                        self.processReceipt()
                    }
                    
                }
                break
            
            case SKPaymentTransactionState.failed:
                print("---- Transaction => Failed")
                SKPaymentQueue.default().finishTransaction(transaction)
                performOnMainQueue {
                    self.fail()
                }
                break
            case SKPaymentTransactionState.restored:
                print("---- Transaction => Restored")
                SKPaymentQueue.default().finishTransaction(transaction)
                performOnMainQueue {
                    self.restoreSucceed()
                    if ApplicationController.jiggle {
                        Config.shared.notifyJigglePurchased()
                    } else {
                        self.processReceipt()
                    }
                }
                break
            case .purchasing:
                print("---- Transaction => Purchasing")
                break
            case .deferred:
                print("---- Transaction => Deferred")
                break
            @unknown default:
                SKPaymentQueue.default().finishTransaction(transaction)
                print("---- Transaction => Unknown")
                break
            }
        }
    }
    
    func paymentQueue(_ queue: SKPaymentQueue, restoreCompletedTransactionsFailedWithError error: Error) {
        restoreFail()
    }
    
    public func paymentQueueRestoreCompletedTransactionsFinished(_ queue: SKPaymentQueue) {

    }
    
    func paymentQueue(_ queue: SKPaymentQueue, removedTransactions transactions: [SKPaymentTransaction]) {
        
    }
    
    func paymentQueue(_ queue: SKPaymentQueue, updatedDownloads downloads: [SKDownload]) {
        
    }
    
    class func postNotification(_ notificationName: StoreManagerNotification) {
        performOnMainQueue {
            let notification = Notification(name: Notification.Name(notificationName.rawValue), object: nil, userInfo: nil)
            NotificationCenter.default.post(notification)
        }
    }
    
    func jiggleSetUp(sharedSecret secret: String) {
        sharedSecret = "\(secret)"
    }
    
    func bounceSetUp(sharedSecret secret: String) {
        sharedSecret = "\(secret)"
        //processReceipt()
        self.processReceiptIfNew()
    }
}

*/
