# QStripe

QStripe is a client for Stripe's REST API. It is completely compatible for use with QML.

# Current Status

- Card
    + [X] Create Card
    + [X] Delete Card
    + [X] Create Token
    + [X] Fetch Token
- Customer
    + [X] Create Customer
    + [X] Update Customer
    + [X] Delete Customer
- Stripe
    + [X] Fetch Customer
    + [X] Fetch Card

# TODO

- Card
    + [ ] Update Card
- Customer
    + [ ] Fetch Cards
    + [ ] Create Charge
    + [ ] Create Charges
- Stripe
    + [ ] Fetch Customers
- Charge
    + [ ] Create Charge
    + [ ] Update Charge
    + [ ] Capture Charge


# Classes

A Stripe instance has children of `Customer` objects.
A `Customer` has children of `Card` objects.
And a `Card` has children of `Token` objects.

## Stripe

`Stripe` instance stores the essential information to send requests to the Stripe API (e.g Public key, secret key.).
When any other class needs to interact with the Stripe API, they use `Stripe` to set the required headers.

### Fetch Customer

You fetch the customer using `Stripe`. Once it is fetched, `customerFetched(Customer *)` signal will be emitted and the
parent of the created `Customer` will be the `Stripe` instance. You can change the parent of the `Customer` If you want.
But If you don't change it, the created `Customer` will be deleted when the `Stripe` instance is deleted.

```qml
Stripe {
    id: stripe
    publishableKey: "PUBLISHABLE_KEY"
    secretKey: "SECRET_KEY"
    onCustomerFetched: {
        console.log("Customer is fetched:", customer.customerID;
    }
    Component.onCompleted: {
        fetchCustomer("cus_sakdjh3ehjkf");
    }
}
```

### Fetch Card

You fetch the card using `Stripe`. Once it is fetched, `cardFetched(Card *)` signal will be emitted and the
parent of the created `Card` will be the `Stripe` instance. You can change the parent of the `Card` If you want.
But If you don't change it, the created `Card` will be deleted when the `Stripe` instance is deleted.

```qml
Stripe {
    id: stripe
    publishableKey: "PUBLISHABLE_KEY"
    secretKey: "SECRET_KEY"
    onCardFetched: {
        console.log("Card is fetched:", card.cardID;
    }
    Component.onCompleted: {
        fetchCard("card_sakdjh3ehjkf");
    }
}
```

## Card

A `Card` instance contains the details of a credit card. You can use the following methods to determine If a card instance
is valid or not.

- validCVC()
- validCardNumber()
- validCardLenght()
- validExpirationMonth()
- validExpirationYear()
- validCard(): This checks for all of the above.

### Create Card Token

Once you set the required fields to a `Card` instance, you can use `createToken()` method to tokenize the card information.

```qml
Stripe {
    id: stripe
    publishableKey: "PUBLISHABLE_KEY"
    secretKey: "SECRET_KEY"

    Customer {
        id: customer

        Card {
            id: card
            cvc: "123"
            cardNumber: "4242424242424242"
            expirationMonth: 3
            expirationYear: 2025
            country: "ca"
            onTokenCreated: {
                // The cardToken will have the same information as token.
                // token is the Token instance.
                console.log(token.tokenID);
            }

            Token {
                id: cardToken
            }
        }
    }
}
```

### Retrieve Token

You can fetch a token using `Card::fetchToken()`. When a token is fetched, the card instance will be updated according to
the `card` field of the fetched token.

```qml
Stripe {
    id: stripe
    publishableKey: "PUBLISHABLE_KEY"
    secretKey: "SECRET_KEY"

    Customer {
        id: customer

        Card {
            id: card
            onTokenFetched: {
                // The cardToken will have the same information as token.
                // token is the Token instance.
                console.log(token.tokenID);
                // Since the Card instance is also updated, this will have a valid value.
                console.log(token.cardID);
            }

            Token {
                id: cardToken
            }
        }
    }
}
```

### Create Card

After you tokenize the card, you can create a card for the customer.
Now, `Card::create()` method need a customer ID to create the card for that customer. There are 3 ways of doing this.

- Set the `customerID` property of the `Card` object. This ID will be used when creating the card.
- Add the `Card` to a `Customer` instance that has an ID. The following uses this option.
- Explicitly pass the customer ID to `Card::create()`.

```qml
Stripe {
    id: stripe
    publishableKey: "PUBLISHABLE_KEY"
    secretKey: "SECRET_KEY"
    onSomeEvent: {
        card.create();
    }

    // This is a valid Customer with an ID.
    Customer {
        id: customer

        // Tokenized card.
        Card {
            id: card
            onCreated: {
                console.log(card.cardID);
            }

            Token {
                id: cardToken
            }
        }
    }
}
```

### Delete Card

You can delete a card using the `Card::deleteCard()` method. To delete a `Card`, that card must have an ID. Otherwise
the method will return false.

```qml
Stripe {
    id: stripe
    publishableKey: "PUBLISHABLE_KEY"
    secretKey: "SECRET_KEY"
    onSomeEvent: {
        card.deleteCard();
    }

    Customer {
        id: customer

        Card {
            id: card
            onDeleted: {
                console.log("Card deleted!");
            }
        }
    }
}
```

## Customer

A `Customer` objects stores the details of a customer.

### Create Customer

You can create a customer by calling `Customer::create()`. This method will not work If you call it on a customer instance
that has an ID.

```qml
Stripe {
    id: stripe
    publishableKey: "PUBLISHABLE_KEY"
    secretKey: "SECRET_KEY"
    onSomeEvent: {
        customer.create();
    }

    Customer {
        id: customer
        email: "foo@bar.com"
        onCreated: {
            console.log("Customer created:", customerID);
        }
    }
}
```

### Update Customer

You can update a customer by calling `Customer::update()`. This method will not work If you call it on a customer instance
that does not have an ID.

```qml
Stripe {
    id: stripe
    publishableKey: "PUBLISHABLE_KEY"
    secretKey: "SECRET_KEY"
    onSomeEvent: {
        customer.email = "foo2@bar2.com";
        customer.update();
    }

    // A customer instance with an ID.
    Customer {
        id: customer
        email: "foo@bar.com"
        onUpdated: {
            console.log("Customer updated:", customerID);
        }
    }
}
```

### Delete Customer

You can delete a customer by calling `Customer::deleteCustomer()`. This method will not work If you call it on a customer instance
that does not have an ID.

```qml
Stripe {
    id: stripe
    publishableKey: "PUBLISHABLE_KEY"
    secretKey: "SECRET_KEY"
    onSomeEvent: {
        customer.deleteCustomer();
    }

    // A customer instance with an ID.
    Customer {
        id: customer
        email: "foo@bar.com"
        onDeleted: {
            // Since it is deleted, customerID will be an empty string.
            console.log("Customer deleted:", customerID);
        }
    }
}
```
