//
//  OSStoreManager.m
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 10/19/20.
//  Copyright © 2020 Froggy Studios. All rights reserved.
//

#import "OSStoreManager.h"
#include "core_includes.h"
#include "FApp.hpp"

@implementation OSStoreManager

- (id) init {
    self = [super init];
    
    [[SKPaymentQueue defaultQueue] addTransactionObserver: self];
    
    self.productIdentifier = @"unknown";
    
    return self;
}

- (void) purchaseProduct: (NSString *)productIdentifier {
    self.restoring = false;
    [self.productRequest cancel];
    self.productRequest.delegate = nil;
    self.productRequest = nil;
    
    
    
    
    
    
    NSMutableSet *aSet = [[NSMutableSet alloc] init];
    if (productIdentifier != NULL) {
        [aSet addObject: productIdentifier];
        self.productIdentifier = productIdentifier;
    }
    
    self.productRequest = [[SKProductsRequest alloc] initWithProductIdentifiers: aSet];
    self.productRequest.delegate = self;
    
    [self.productRequest start];
}

- (void) restorePurchases {
    self.restoring = true;
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}



//SKRequestDelegate

- (void)requestDidFinish:(SKRequest *)request {
    NSLog(@"requestDidFinish: %@", request);
    
    
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error {
    NSLog(@"request: %@ didFailWithError: %@", request, error.localizedDescription);
    
}


//SKProductsRequestDelegate

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
    NSLog(@"productsRequest: %@ didReceiveResponse: %@", request, response);
    
    if (response.invalidProductIdentifiers.count > 0) {
        NSLog(@"Invalid Product ID's:");
        for (NSString *aProductIdentifier in response.invalidProductIdentifiers) {
            NSLog(@"Identifier: [%@]\n", aProductIdentifier);
        }
    }
    if (response.products.count > 0) {
        for (SKProduct *aProduct in response.products) {
            SKPayment *aPayment = [SKPayment paymentWithProduct: aProduct];
            [[SKPaymentQueue defaultQueue] addPayment: aPayment];
        }
    }
}

//SKPaymentTransactionObserver

// Sent when the transaction array has changed (additions or state changes).  Client should check state of transactions and finish as appropriate.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray<SKPaymentTransaction *> *)transactions {
    
    for (SKPaymentTransaction *transaction in transactions) {
        FString aProductID = [transaction.payment.productIdentifier UTF8String];
        
        switch (transaction.transactionState) {
            case SKPaymentTransactionStatePurchased:
                NSLog(@"transaction %@ state = SKPaymentTransactionStatePurchased", transaction);
                
                if (gAppBase != NULL) {
                    if (self.restoring == YES) {
                        gAppBase->PurchaseRestoreSuccess(aProductID);
                    } else {
                        gAppBase->PurchaseSuccess(aProductID);
                    }
                }
                
                [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
                
                break;
                
            case SKPaymentTransactionStateFailed:
                NSLog(@"transaction %@ state = SKPaymentTransactionStateFailed", transaction);
                
                if (gAppBase != NULL) {
                    if (self.restoring == YES) {
                        gAppBase->PurchaseRestoreFailure(aProductID);
                    } else {
                        gAppBase->PurchaseFailure(aProductID);
                    }
                }
                
                [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
                
                break;
                
            case SKPaymentTransactionStateRestored:
                NSLog(@"transaction %@ state = SKPaymentTransactionStateRestored", transaction);
                if (gAppBase != NULL) {
                    gAppBase->PurchaseRestoreFailure(aProductID);
                }
                break;
                
            case SKPaymentTransactionStateDeferred:
                NSLog(@"transaction %@ state = SKPaymentTransactionStateDeferred", transaction);
                if (gAppBase != NULL) {
                    gAppBase->PurchaseDeferred(aProductID);
                }
                break;
            default:
                break;
        }
    }
}

- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions:(NSArray<SKPaymentTransaction *> *)transactions {
    NSLog(@"paymentQueue: %@ removedTransactions: %@", queue, transactions);
}

// Sent when an error is encountered while adding transactions from the user's purchase history back to the queue.
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error {
    NSLog(@"paymentQueue: %@ restoreCompletedTransactionsFailedWithError: %@", queue, error.localizedDescription);
}

// Sent when all transactions from the user's purchase history have successfully been added back to the queue.
- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue {
    NSLog(@"paymentQueueRestoreCompletedTransactionsFinished: %@", queue);
}

// Sent when the download state has changed.
- (void)paymentQueue:(SKPaymentQueue *)queue updatedDownloads:(NSArray<SKDownload *> *)downloads {
    NSLog(@"paymentQueue: %@ updatedDownloads: %@", queue, downloads);
}

- (void)dealloc {
    NSLog(@"Store Dealloc...\n");
}

@end
