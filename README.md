# QStripe

QStripe is a client for Stripe's REST API. It is completely compatible for use with QML.

# Classes

A Stripe instance has children of `Customer` objects.
A `Customer` has children of `Card` objects.
And a `Card` has children of `Token` objects.

## Stripe

This is the main class that carries out the operations with the API. All the other classes are only used to store information that this class and the Stripe
API needs to operate on.

### Create Card Token

You can create a card token by passing the card instance tho `createToken()` method.

```qml
Stripe {
    id: stripe
    publishableKey: "PUBLISHABLE_KEY"

    Customer {
        id: customer

        Card {
            id: card
            onCardTokenCreated: {
                // token is the Token instance.
                console.log(token.id);
                // You can also copy the token instance to an existing one for convenience.
                cardToken.set(token);
            }

            Token {
                id: cardToken
            }
        }
    }
}
```

### Retrieve Customer

You are likely only keeping the `Customer` ID on your server. Using that ID, you can retrieve the customer details using `retrieveCustomer()` method.

```qml
Stripe {
    id: stripe
    publishableKey: "PUBLISHABLE_KEY"
    onCustomerRetrieved: {
        // customer is the Customer instance.
        console.log(customer.id);
        // You can also copy the customer instance to an existing one for convenience.
        stripeCustomer.set(customer);
    }

    Customer {
        id: stripeCustomer
    }
}
```

### Retrieve Token

You are likely only keeping the `Token` ID on your server. Using that ID, you can retrieve the token details using `retrieveToken()` method.

```qml
Stripe {
    id: stripe
    publishableKey: "PUBLISHABLE_KEY"
    onTokenRetrieved: {
        // token is the Token instance.
        console.log(token.id);
        // You can also copy the token instance to an existing one for convenience.
        cardToken.set(token);
    }

    Customer {
        id: customer

        Card {
            id: card

            Token {
                id: cardToken
            }
        }
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

## Customer

A `Customer` objects stores the details of a customer. You can attach a token to the customer by using the `attachToken()` method. If the customer already has
an attached token, the new token will be the defualt one.
