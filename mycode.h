// Socket.io setup
const socket = io();

// Event listener for incoming chat messages
socket.on('chat message', (msg) => {
  $('#messages').append($('<li>').text(`${msg.user}: ${msg.msg}`));
});

// Function to send a chat message
function sendMessage() {
  const message = $('#m').val();
  if (message) {
    socket.emit('chat message', message);
    $('#m').val('');
  }
}

// Event listener for user authentication notification
socket.on('auth notification', (message) => {
  alert(message);
});

// Function to notify the server about user authentication
function notifyAuth() {
  socket.emit('auth notification', 'User authenticated!');
}

// Add more scripts as needed
<script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
<script src="/socket.io/socket.io.js"></script>
<script src="/js/main.js"></script>
// Socket.io setup
const socket = io();

// Event listener for incoming chat messages
socket.on('chat message', (msg) => {
  $('#messages').append($('<li>').text(`${msg.user}: ${msg.msg}`));
});

// Function to send a chat message
function sendMessage() {
  const message = $('#m').val();
  if (message) {
    socket.emit('chat message', message);
    $('#m').val('');
  }
}

// Add more scripts as needed
<link rel="stylesheet" href="/css/style.css">
body {
    font-family: 'Arial', sans-serif;
    margin: 0;
    padding: 0;
    background-color: #f4f4f4;
}

h1, h2, p {
    color: #333;
}

.container {
    width: 80%;
    margin: 0 auto;
}

nav {
    background-color: #333;
    padding: 10px;
}

nav a {
    color: #fff;
    text-decoration: none;
    margin-right: 15px;
}

button {
    background-color: #4caf50;
    color: #fff;
    padding: 10px;
    border: none;
    cursor: pointer;
}

button:hover {
    background-color: #45a049;
}

ul {
    list-style-type: none;
    padding: 0;
}

li {
    margin-bottom: 10px;
}

form {
    margin-top: 20px;
}

#messages {
    list-style-type: none;
    padding: 0;
}

#messages li {
    margin-bottom: 10px;
}

/* Add more styles as needed */
<!-- Chat view -->
<h2>Live Chat</h2>
<ul id="messages"></ul>
<form action="" id="form" autocomplete="off">
  <input id="m" autocomplete="off" /><button onclick="sendMessage()">Send</button>
</form>
<!-- Add more content as needed -->
<!-- Order Details view -->
<h2>Order Details - Order #{{order.orderNumber}}</h2>
<p>Total: ${{order.total}}</p>
<ul>
  {{#each order.products}}
    <li>{{this.product.name}} - Quantity: {{this.quantity}} - ${{this.product.price}}</li>
  {{/each}}
</ul>
<!-- Add more content as needed -->
<!-- Order History view -->
<h2>Your Order History</h2>
{{#each orders}}
  <p><a href="/order-details/{{this._id}}">Order #{{this.orderNumber}} - Total: ${{this.total}}</a></p>
{{/each}}
<!-- Add more content as needed -->
<!-- Checkout view -->
<h2>Checkout</h2>
<form action="/process-payment" method="post">
  {{#each cart}}
    <p>{{this.product.name}} - Quantity: {{this.quantity}} - Price: ${{this.product.price}}</p>
  {{/each}}
  <p>Total: ${{totalAmount}}</p>
  <label for="paymentMethod">Payment Method:</label>
  <input type="text" id="paymentMethod" name="paymentMethodId" required>
  <button type="submit">Proceed to Payment</button>
</form>
<!-- Add more content as needed -->
<!-- Cart view -->
<h2>Your Shopping Cart</h2>
{{#each cart}}
  <p>{{this.product.name}} - Quantity: {{this.quantity}} - Price: ${{this.product.price}}</p>
{{/each}}
<button onclick="checkout()">Proceed to Checkout</button>
<!-- Add more content as needed -->
<!-- Product Details view -->
<h2>{{product.name}}</h2>
<p>Description: {{product.description}}</p>
<p>Price: ${{product.price}}</p>
<button onclick="addToCart('{{product._id}}')">Add to Cart</button>
<!-- Add more content as needed -->
<!-- Home view -->
<h1>Welcome to Your E-Commerce Website</h1>
{{#if user}}
  <p>Hello, {{user.username}}!</p>
{{else}}
  <p>Not logged in. <a href="/login">Login</a> or <a href="/register">Register</a></p>
{{/if}}
<!-- Add more content as needed -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="/css/style.css">
    <title>Your E-Commerce Website</title>
</head>
<body>
    {{{body}}}

    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <script src="/socket.io/socket.io.js"></script>
    <script src="/js/main.js"></script>
</body>
</html>
const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const orderSchema = new Schema({
  user: { type: Schema.Types.ObjectId, ref: 'User', required: true },
  products: [{ product: { type: Schema.Types.ObjectId, ref: 'Product' }, quantity: Number }],
  total: { type: Number, required: true },
  orderNumber: { type: String, required: true },
  status: { type: String, default: 'Pending' },
}, { timestamps: true });

module.exports = mongoose.model('Order', orderSchema);
const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const productSchema = new Schema({
  name: { type: String, required: true },
  description: { type: String, required: true },
  price: { type: Number, required: true },
});

module.exports = mongoose.model('Product', productSchema);
const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const userSchema = new Schema({
  username: { type: String, required: true, unique: true },
  password: { type: String, required: true },
  cart: [{ product: { type: Schema.Types.ObjectId, ref: 'Product' }, quantity: Number }],
  orders: [{ type: Schema.Types.ObjectId, ref: 'Order' }],
});

module.exports = mongoose.model('User', userSchema);
const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const mongoose = require('mongoose');
const session = require('express-session');
const passport = require('passport');
const MongoStore = require('connect-mongo')(session);
const bodyParser = require('body-parser');
const socketIoSession = require('express-socket.io-session');
const stripe = require('stripe')('your_stripe_secret_key');

const app = express();
const server = http.createServer(app);
const io = socketIo(server);

// Load environment variables
require('dotenv').config();

// Database connection
mongoose.connect(process.env.MONGODB_URI, { useNewUrlParser: true, useUnifiedTopology: true });
mongoose.set('useCreateIndex', true);
mongoose.set('useFindAndModify', false);

// Set up middleware, routes, and other configurations...
app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static('public'));
app.set('view engine', 'handlebars');

// Express Session
const sessionMiddleware = session({
  secret: 'your_secret_key',
  resave: false,
  saveUninitialized: false,
  store: new MongoStore({ mongooseConnection: mongoose.connection }),
});
app.use(sessionMiddleware);

// Passport Middleware
app.use(passport.initialize());
app.use(passport.session());

// Socket.io setup
io.use(socketIoSession(sessionMiddleware, { autoSave: true }));

io.on('connection', (socket) => {
  const user = socket.handshake.session.passport ? socket.handshake.session.passport.user : null;

  if (user) {
    io.to(socket.id).emit('message', 'Welcome to the chat!');

    socket.on('chat message', (msg) => {
      io.emit('chat message', { user, msg });
    });
  }
});

// Other configurations and routes...

server.listen(process.env.PORT || 3000, () => {
  console.log('Server listening on port 3000');
});
/project-root
|-- /controllers
|   |-- authController.js
|   |-- productController.js
|   |-- searchController.js
|   |-- cartController.js
|   |-- checkoutController.js
|   |-- orderHistoryController.js
|   |-- chatController.js
|
|-- /middlewares
|   |-- authMiddleware.js
|
|-- /models
|   |-- User.js
|   |-- Product.js
|   |-- Order.js
|
|-- /public
|   |-- /css
|   |   |-- style.css
|   |-- /js
|   |   |-- main.js
|
|-- /routes
|   |-- authRoutes.js
|   |-- productRoutes.js
|   |-- searchRoutes.js
|   |-- cartRoutes.js
|   |-- checkoutRoutes.js
|   |-- orderHistoryRoutes.js
|   |-- chatRoutes.js
|
|-- /views
|   |-- auth
|   |   |-- login.handlebars
|   |   |-- register.handlebars
|   |-- cart.handlebars
|   |-- chat.handlebars
|   |-- checkout.handlebars
|   |-- home.handlebars
|   |-- order-details.handlebars
|   |-- order-history.handlebars
|   |-- payment-fail.handlebars
|   |-- payment-success.handlebars
|   |-- product-details.handlebars
|   |-- search-results.handlebars
|   |-- layout.handlebars
|
|-- /config
|   |-- keys.js
|
|-- app.js
|-- package.json
|-- README.md
<!-- Chat view -->
<h2>Live Chat</h2>
<ul id="messages"></ul>
<form action="" id="form" autocomplete="off">
  <input id="m" autocomplete="off" /><button>Send</button>
</form>

<script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
<script src="/socket.io/socket.io.js"></script>
<script>
  $(function () {
    const socket = io();

    // Display incoming messages
    socket.on('chat message', (msg) => {
      $('#messages').append($('<li>').text(`${msg.user}: ${msg.msg}`));
    });

    // Send chat messages
    $('#form').submit((e) => {
      e.preventDefault();
      if ($('#m').val()) {
        socket.emit('chat message', $('#m').val());
        $('#m').val('');
      }
    });
  });
</script>
const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const session = require('express-session');
const app = express();
const server = http.createServer(app);
const io = socketIo(server);

// Other setup...

// Socket.io setup
const sessionMiddleware = session({
  secret: 'your_secret_key',
  resave: false,
  saveUninitialized: false,
});

app.use(sessionMiddleware);
io.use((socket, next) => {
  sessionMiddleware(socket.request, {}, next);
});

// Other middleware...

io.on('connection', (socket) => {
  const user = socket.request.session.passport ? socket.request.session.passport.user : null;

  if (user) {
    // Notify user of connection
    io.to(socket.id).emit('message', 'Welcome to the chat!');

    // Handle chat messages
    socket.on('chat message', (msg) => {
      io.emit('chat message', { user, msg });
    });
  }
});

// Other routes...

server.listen(3000, () => {
  console.log('Server listening on port 3000');
});
npm install socket.io express-session
<!-- Order Details view -->
<h2>Order Details - Order #{{order.orderNumber}}</h2>
<p>Total: ${{order.total}}</p>
<ul>
  {{#each order.products}}
    <li>{{this.product.name}} - Quantity: {{this.quantity}} - ${{this.product.price}}</li>
  {{/each}}
</ul>
<!-- Order History view -->
<h2>Your Order History</h2>
{{#if orders.length}}
  <ul>
    {{#each orders}}
      <li><a href="/order-details/{{this._id}}">Order #{{this.orderNumber}} - Total: ${{this.total}}</a></li>
    {{/each}}
  </ul>
{{else}}
  <p>No order history available.</p>
{{/if}}
<!-- Order History view -->
<h2>Your Order History</h2>
{{#if orders.length}}
  <ul>
    {{#each orders}}
      <li><a href="/order-details/{{this._id}}">Order #{{this.orderNumber}} - Total: ${{this.total}}</a></li>
    {{/each}}
  </ul>
{{else}}
  <p>No order history available.</p>
{{/if}}
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/order-history', authMiddleware.ensureAuthenticated, orderHistoryController.getOrderHistory);
router.get('/order-details/:id', authMiddleware.ensureAuthenticated, orderHistoryController.getOrderDetails);
exports.getOrderHistory = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('orders.product');
    res.render('order-history', { orders: user.orders });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.getOrderDetails = async (req, res) => {
  const orderId = req.params.id;

  try {
    const user = await User.findById(req.user._id).populate('orders.product');
    const order = user.orders.find(order => order._id.toString() === orderId);

    if (!order) {
      return res.redirect('/order-history'); // Order not found, redirect to history
    }

    res.render('order-details', { order });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Payment Fail view -->
<h2>Payment Failed</h2>
<p>There was an issue processing your payment. Please try again.</p>
<!-- Payment Success view -->
<h2>Payment Successful</h2>
<p>Your payment was successful. Order number: {{orderNumber}}</p>
<!-- Checkout view -->
<h2>Checkout</h2>
<form action="/process-payment" method="post">
  <!-- Display cart items with quantity and price -->
  {{#each cartItems}}
    <p>{{this.product.name}} - Quantity: {{this.quantity}} - Price: ${{this.product.price}}</p>
  {{/each}}

  <!-- Display total amount -->
  <p>Total: ${{totalAmount}}</p>

  <!-- Payment method input (can be a card input provided by Stripe Elements) -->
  <label for="paymentMethod">Payment Method:</label>
  <input type="text" id="paymentMethod" name="paymentMethodId" required>

  <button type="submit">Proceed to Payment</button>
</form>
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/checkout', authMiddleware.ensureAuthenticated, checkoutController.initiateCheckout);
router.post('/process-payment', authMiddleware.ensureAuthenticated, checkoutController.processPayment);
const stripe = require('stripe')('your_stripe_secret_key');

exports.initiateCheckout = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.product');
    res.render('checkout', { cartItems: user.cart });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.processPayment = async (req, res) => {
  const { paymentMethodId } = req.body;

  try {
    const user = await User.findById(req.user._id).populate('cart.product');

    // Create a PaymentIntent with the order total and a payment method
    const paymentIntent = await stripe.paymentIntents.create({
      amount: calculateTotalAmount(user.cart),
      currency: 'usd',
      payment_method: paymentMethodId,
      confirmation_method: 'manual',
      confirm: true,
    });

    // Clear the user's cart after successful payment
    user.cart = [];
    await user.save();

    res.render('payment-success', { orderNumber: generateOrderNumber() });
  } catch (err) {
    console.error(err);
    res.render('payment-fail'); // Handle error
  }
};

function calculateTotalAmount(cart) {
  return cart.reduce((total, item) => total + item.product.price * item.quantity, 0);
}

function generateOrderNumber() {
  return Math.floor(100000 + Math.random() * 900000);
}
<!-- Cart Success view -->
<h2>Product Added to Cart Successfully!</h2>
<p>The selected product has been added to your shopping cart.</p>
<!-- Cart view -->
<h2>Your Shopping Cart</h2>
{{#if cartItems.length}}
  <ul>
    {{#each cartItems}}
      <li>
        {{this.product.name}} - Quantity: {{this.quantity}} - Price: ${{this.product.price}}
      </li>
    {{/each}}
  </ul>
{{else}}
  <p>Your shopping cart is empty.</p>
{{/if}}
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/cart', authMiddleware.ensureAuthenticated, cartController.getCartPage);
router.get('/add-to-cart/:id', authMiddleware.ensureAuthenticated, cartController.addToCart);
exports.addToCart = async (req, res) => {
  const productId = req.params.id;

  try {
    const user = await User.findById(req.user._id);

    // Check if the product is already in the cart
    const cartItem = user.cart.find(item => item.product.toString() === productId);

    if (cartItem) {
      cartItem.quantity += 1; // Increase quantity if product is already in the cart
    } else {
      user.cart.push({ product: productId, quantity: 1 });
    }

    await user.save();

    res.render('cart-success');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.getCartPage = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.product');
    res.render('cart', { cartItems: user.cart });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Advanced Search Results view -->
<h2>Advanced Search Results for "{{keyword}}"</h2>
<p>Price Range: ${{minPrice}} - ${{maxPrice}}</p>

{{#if products.length}}
  <ul>
    {{#each products}}
      <li>{{this.name}} - Price: ${{this.price}}</li>
    {{/each}}
  </ul>

  <!-- Pagination -->
  <div>
    {{#if (gt totalPages 1)}}
      {{#each pages}}
        <a href="/advanced-search?page={{this}}&keyword={{keyword}}&minPrice={{minPrice}}&maxPrice={{maxPrice}}&sortBy={{sortBy}}">
          {{this}}
        </a>
      {{/each}}
    {{/if}}
  </div>
{{else}}
  <p>No results found for "{{keyword}}".</p>
{{/if}}
router.get('/advanced-search', searchController.advancedSearchProducts);
const ITEMS_PER_PAGE = 10;

exports.advancedSearchProducts = async (req, res) => {
  const { keyword, minPrice, maxPrice, sortBy, page } = req.query;
  const skip = (page - 1) * ITEMS_PER_PAGE;

  try {
    const query = {
      $or: [
        { name: { $regex: keyword, $options: 'i' } },
        { description: { $regex: keyword, $options: 'i' } }
      ],
      price: { $gte: minPrice || 0, $lte: maxPrice || Number.MAX_SAFE_INTEGER }
    };

    const sortOptions = {};
    if (sortBy === 'price-asc') {
      sortOptions.price = 1;
    } else if (sortBy === 'price-desc') {
      sortOptions.price = -1;
    }

    const products = await Product.find(query)
      .sort(sortOptions)
      .skip(skip)
      .limit(ITEMS_PER_PAGE);

    const totalProducts = await Product.countDocuments(query);
    const totalPages = Math.ceil(totalProducts / ITEMS_PER_PAGE);

    res.render('advanced-search-results', {
      keyword,
      minPrice,
      maxPrice,
      sortBy,
      products,
      page: parseInt(page),
      totalPages
    });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Search Results view -->
<h2>Search Results for "{{keyword}}"</h2>
{{#if products.length}}
  <ul>
    {{#each products}}
      <li>{{this.name}} - Price: ${{this.price}}</li>
    {{/each}}
  </ul>
{{else}}
  <p>No results found for "{{keyword}}".</p>
{{/if}}
router.get('/search', searchController.searchProducts);
exports.searchProducts = async (req, res) => {
  const keyword = req.query.keyword;

  try {
    const products = await Product.find({
      $or: [
        { name: { $regex: keyword, $options: 'i' } }, // Case-insensitive search for product name
        { description: { $regex: keyword, $options: 'i' } } // Case-insensitive search for product description
      ]
    });

    res.render('search-results', { keyword, products });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Wishlist Fail view -->
<h2>Product Already in Wishlist</h2>
<p>{{message}}</p>
<!-- Wishlist Success view -->
<h2>Product Added to Wishlist Successfully!</h2>
<p>The selected product has been added to your wishlist.</p>
<!-- Wishlist view -->
<h2>Your Wishlist</h2>
{{#if wishlist.length}}
  <ul>
    {{#each wishlist}}
      <li>{{this.name}} - Price: ${{this.price}}</li>
    {{/each}}
  </ul>
{{else}}
  <p>Your wishlist is empty.</p>
{{/if}}
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/wishlist', authMiddleware.ensureAuthenticated, wishlistController.getWishlistPage);
router.get('/add-to-wishlist/:id', authMiddleware.ensureAuthenticated, wishlistController.addToWishlist);
<!-- Advanced Search Results view -->
<h2>Advanced Search Results for "{{keyword}}"</h2>
<p>Price Range: ${{minPrice}} - ${{maxPrice}}</p>

{{#if products.length}}
  <ul>
    {{#each products}}
      <li>{{this.name}} - Price: ${{this.price}}</li>
    {{/each}}
  </ul>

  <!-- Pagination -->
  <div>
    {{#if (gt totalPages 1)}}
      {{#each pages}}
        <a href="/advanced-search?page={{this}}&keyword={{keyword}}&minPrice={{minPrice}}&maxPrice={{maxPrice}}&sortBy={{sortBy}}">
          {{this}}
        </a>
      {{/each}}
    {{/if}}
  </div>
{{else}}
  <p>No results found for "{{keyword}}".</p>
{{/if}}
router.get('/advanced-search', searchController.advancedSearchProducts);
const ITEMS_PER_PAGE = 10;

exports.advancedSearchProducts = async (req, res) => {
  const { keyword, minPrice, maxPrice, sortBy, page } = req.query;
  const skip = (page - 1) * ITEMS_PER_PAGE;

  try {
    const query = {
      $or: [
        { name: { $regex: keyword, $options: 'i' } },
        { description: { $regex: keyword, $options: 'i' } }
      ],
      price: { $gte: minPrice || 0, $lte: maxPrice || Number.MAX_SAFE_INTEGER }
    };

    const sortOptions = {};
    if (sortBy === 'price-asc') {
      sortOptions.price = 1;
    } else if (sortBy === 'price-desc') {
      sortOptions.price = -1;
    }

    const products = await Product.find(query)
      .sort(sortOptions)
      .skip(skip)
      .limit(ITEMS_PER_PAGE);

    const totalProducts = await Product.countDocuments(query);
    const totalPages = Math.ceil(totalProducts / ITEMS_PER_PAGE);

    res.render('advanced-search-results', {
      keyword,
      minPrice,
      maxPrice,
      sortBy,
      products,
      page: parseInt(page),
      totalPages
    });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Search Results view -->
<h2>Search Results for "{{keyword}}"</h2>
{{#if products.length}}
  <ul>
    {{#each products}}
      <li>{{this.name}} - Price: ${{this.price}}</li>
    {{/each}}
  </ul>
{{else}}
  <p>No results found for "{{keyword}}".</p>
{{/if}}
router.get('/search', searchController.searchProducts);
exports.searchProducts = async (req, res) => {
  const keyword = req.query.keyword;

  try {
    const products = await Product.find({
      $or: [
        { name: { $regex: keyword, $options: 'i' } }, // Case-insensitive search for product name
        { description: { $regex: keyword, $options: 'i' } } // Case-insensitive search for product description
      ]
    });

    res.render('search-results', { keyword, products });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Wishlist Fail view -->
<h2>Product Already in Wishlist</h2>
<p>{{message}}</p>
<!-- Wishlist Success view -->
<h2>Product Added to Wishlist Successfully!</h2>
<p>The selected product has been added to your wishlist.</p>
<!-- Wishlist view -->
<h2>Your Wishlist</h2>
{{#if wishlist.length}}
  <ul>
    {{#each wishlist}}
      <li>{{this.name}} - Price: ${{this.price}}</li>
    {{/each}}
  </ul>
{{else}}
  <p>Your wishlist is empty.</p>
{{/if}}
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/wishlist', authMiddleware.ensureAuthenticated, wishlistController.getWishlistPage);
router.get('/add-to-wishlist/:id', authMiddleware.ensureAuthenticated, wishlistController.addToWishlist);
exports.addToWishlist = async (req, res) => {
  const productId = req.params.id;

  try {
    const user = await User.findById(req.user._id);

    // Check if the product is already in the wishlist
    if (user.wishlist.includes(productId)) {
      return res.render('wishlist-fail', { message: 'Product is already in your wishlist.' });
    }

    // Add the product to the wishlist
    user.wishlist.push(productId);
    await user.save();

    res.render('wishlist-success');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.getWishlistPage = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('wishlist');
    res.render('wishlist', { wishlist: user.wishlist });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Product Details view -->
<h2>{{product.name}}</h2>
<p>{{product.description}}</p>
<p>Price: ${{product.price}}</p>

{{#if product.reviews.length}}
  <h3>Reviews:</h3>
  <ul>
    {{#each product.reviews}}
      <li>
        <strong>{{this.user.name}}</strong> - Rating: {{this.rating}}
        <p>{{this.reviewText}}</p>
      </li>
    {{/each}}
  </ul>
{{else}}
  <p>No reviews available for this product.</p>
{{/if}}
router.get('/product-details/:id', productController.getProductDetailsPage);
exports.getProductDetailsPage = async (req, res) => {
  const productId = req.params.id;

  try {
    const product = await Product.findById(productId).populate('reviews.user');
    res.render('product-details', { product });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Review Fail view -->
<h2>Review Submission Failed</h2>
<p>{{message}}</p>
<!-- Review Success view -->
<h2>Review Submitted Successfully!</h2>
<p>Thank you for your review.</p>
<!-- Write Review Page view -->
<h2>Write a Review for {{product.name}}</h2>
<form action="/submit-review" method="post">
  <input type="hidden" name="productId" value="{{product._id}}">
  <label for="rating-input">Rating:</label>
  <select id="rating-input" name="rating" required>
    <option value="1">1 - Terrible</option>
    <option value="2">2 - Poor</option>
    <option value="3">3 - Average</option>
    <option value="4">4 - Good</option>
    <option value="5">5 - Excellent</option>
  </select>
  <label for="review-text-input">Review Text:</label>
  <textarea id="review-text-input" name="reviewText" required></textarea>
  <button type="submit">Submit Review</button>
</form>
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/write-review/:id', authMiddleware.ensureAuthenticated, reviewController.getWriteReviewPage);
router.post('/submit-review', authMiddleware.ensureAuthenticated, reviewController.postSubmitReview);
exports.getWriteReviewPage = async (req, res) => {
  const productId = req.params.id;

  try {
    const product = await Product.findById(productId);
    res.render('write-review', { product });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.postSubmitReview = async (req, res) => {
  const { productId, rating, reviewText } = req.body;

  try {
    const product = await Product.findById(productId);
    const user = await User.findById(req.user._id);

    // Check if the user has already reviewed the product
    const existingReview = product.reviews.find(review => review.user.toString() === user._id.toString());

    if (existingReview) {
      return res.render('review-fail', { message: 'You have already reviewed this product.' });
    }

    // Add the new review
    const newReview = {
      user: user._id,
      rating: parseInt(rating),
      reviewText
    };

    product.reviews.push(newReview);
    await product.save();

    res.render('review-success');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Delete Account Success view -->
<h2>Account Deleted Successfully</h2>
<p>Your account has been successfully deleted.</p>
<!-- Delete Account Page view -->
<h2>Delete Your Account</h2>
<p>Are you sure you want to delete your account?</p>
<form action="/delete-account" method="post">
  <button type="submit">Yes, Delete My Account</button>
</form>
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/delete-account', authMiddleware.ensureAuthenticated, userController.getDeleteAccountPage);
router.post('/delete-account', authMiddleware.ensureAuthenticated, userController.postDeleteAccount);
exports.getDeleteAccountPage = (req, res) => {
  res.render('delete-account');
};

exports.postDeleteAccount = async (req, res) => {
  try {
    const user = await User.findById(req.user._id);

    // Perform necessary actions for account deletion, such as deleting related data or sending notifications.
    // For simplicity, we'll just display a success message.
    res.render('delete-account-success');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Order Details view -->
<h2>Order Details - Order #{{order.orderNumber}}</h2>
<p>Total: ${{order.total}}</p>
<ul>
  {{#each order.products}}
    <li>{{this.product.name}} - Quantity: {{this.quantity}} - ${{this.product.price}}</li>
  {{/each}}
</ul>
<!-- Order History view -->
<h2>Your Order History</h2>
{{#if orders.length}}
  <ul>
    {{#each orders}}
      <li><a href="/order-details/{{this._id}}">Order #{{this.orderNumber}} - Total: ${{this.total}}</a></li>
    {{/each}}
  </ul>
{{else}}
  <p>No order history available.</p>
{{/if}}
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/order-history', authMiddleware.ensureAuthenticated, orderController.getOrderHistoryPage);
router.get('/order-details/:id', authMiddleware.ensureAuthenticated, orderController.getOrderDetailsPage);
exports.getOrderHistoryPage = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('orders.product');
    res.render('order-history', { orders: user.orders });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.getOrderDetailsPage = async (req, res) => {
  const orderId = req.params.id;

  try {
    const user = await User.findById(req.user._id).populate('orders.product');
    const order = user.orders.find(order => order._id.toString() === orderId);

    if (!order) {
      return res.redirect('/order-history'); // Order not found, redirect to history
    }

    res.render('order-details', { order });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Account Settings Success view -->
<h2>Account Settings Updated Successfully!</h2>
<p>Your account settings have been updated.</p>
<!-- Account Settings Page view -->
<h2>Account Settings</h2>
<form action="/update-account-settings" method="post">
  <label for="name-input">Name:</label>
  <input type="text" id="name-input" name="name" value="{{user.name}}" required>
  <label for="email-input">Email:</label>
  <input type="email" id="email-input" name="email" value="{{user.email}}" required>
  <label for="new-password-input">New Password (optional):</label>
  <input type="password" id="new-password-input" name="newPassword">
  <button type="submit">Save Changes</button>
</form>
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/account-settings', authMiddleware.ensureAuthenticated, userController.getAccountSettingsPage);
router.post('/update-account-settings', authMiddleware.ensureAuthenticated, userController.postUpdateAccountSettings);
exports.getAccountSettingsPage = async (req, res) => {
  try {
    const user = await User.findById(req.user._id);
    res.render('account-settings', { user });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.postUpdateAccountSettings = async (req, res) => {
  const { name, email, newPassword } = req.body;

  try {
    const user = await User.findById(req.user._id);

    // Update user information
    user.name = name;
    user.email = email;

    // Update password if a new one is provided
    if (newPassword) {
      user.password = newPassword;
    }

    await user.save();

    res.render('account-settings-success');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Feedback Success view -->
<h2>Feedback Submitted Successfully!</h2>
<p>Thank you for your feedback. We appreciate your input!</p>
<!-- Contact Page view -->
<h2>Contact Us</h2>
<form action="/submit-feedback" method="post">
  <label for="subject-input">Subject:</label>
  <input type="text" id="subject-input" name="subject" required>
  <label for="message-input">Message:</label>
  <textarea id="message-input" name="message" required></textarea>
  <button type="submit">Submit Feedback</button>
</form>
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/contact', authMiddleware.ensureAuthenticated, contactController.getContactPage);
router.post('/submit-feedback', authMiddleware.ensureAuthenticated, contactController.postSubmitFeedback);
exports.getContactPage = (req, res) => {
  res.render('contact-page');
};

exports.postSubmitFeedback = async (req, res) => {
  const { subject, message } = req.body;

  try {
    // Handle feedback submission logic, e.g., storing in a database or sending an email to administrators.
    // For simplicity, we'll just display a success message.
    res.render('feedback-success');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Invite Code Fail view -->
<h2>Invalid Invite Code</h2>
<p>Sorry, the invite code you entered is not valid.</p>
<!-- Invite Code Success view -->
<h2>Invite Code Successfully Used!</h2>
<p>Congratulations! You've successfully used the invite code.</p>
<!-- Referral Page view -->
<h2>Your Referral Page</h2>
<p>Your Invite Code: {{inviteCode}}</p>
<form action="/use-invite-code" method="post">
  <label for="invite-code-input">Use Invite Code:</label>
  <input type="text" id="invite-code-input" name="inviteCode" required>
  <button type="submit">Use Code</button>
</form>
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/referral-page', authMiddleware.ensureAuthenticated, userController.getReferralPage);
router.post('/use-invite-code', authMiddleware.ensureAuthenticated, userController.postUseInviteCode);
exports.getReferralPage = async (req, res) => {
  try {
    const user = await User.findById(req.user._id);
    const inviteCode = user.inviteCode;

    res.render('referral-page', { inviteCode });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.postUseInviteCode = async (req, res) => {
  const { inviteCode } = req.body;

  try {
    const invitingUser = await User.findOne({ inviteCode });
    if (invitingUser) {
      // Perform actions when a valid invite code is used, e.g., granting discounts, promotions, etc.
      // For simplicity, we'll just display a success message.
      return res.render('invite-code-success');
    }

    res.render('invite-code-fail'); // Displayed when the invite code is invalid
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- User Notifications view -->
<h2>Your Notifications</h2>
{{#if notifications.length}}
  <ul>
    {{#each notifications}}
      <li>{{this}}</li>
    {{/each}}
  </ul>
{{else}}
  <p>No new notifications.</p>
{{/if}}
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/user-notifications', authMiddleware.ensureAuthenticated, userController.getUserNotifications);
exports.getUserNotifications = async (req, res) => {
  try {
    const user = await User.findById(req.user._id);
    const notifications = user.notifications;
    user.notifications = []; // Clear notifications after viewing
    await user.save();

    res.render('user-notifications', { notifications });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Chat view -->
<h2>Real-time Chat</h2>
<div id="chat-box"></div>
<form id="chat-form">
  <input type="text" id="message-input" placeholder="Type your message...">
  <button type="submit">Send</button>
</form>

<script src="https://cdnjs.cloudflare.com/ajax/libs/socket.io/4.0.1/socket.io.js"></script>
<script>
  const socket = io();

  // Listen for incoming chat messages
  socket.on('chatMessage', message => {
    const chatBox = document.getElementById('chat-box');
    chatBox.innerHTML += `<p>${message}</p>`;
  });

  // Handle form submission to send chat messages
  document.getElementById('chat-form').addEventListener('submit', event => {
    event.preventDefault();
    const messageInput = document.getElementById('message-input');
    const message = messageInput.value.trim();

    if (message) {
      socket.emit('chatMessage', message);
      messageInput.value = '';
    }
  });
</script>
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/chat', authMiddleware.ensureAuthenticated, chatController.getChatPage);
exports.getChatPage = (req, res) => {
  res.render('chat');
};
<!-- Order Confirmed view -->
<h2>Order Confirmed</h2>
<p>Your order has been confirmed. Thank you for shopping with us!</p>
<!-- Checkout view -->
<h2>Review Your Order</h2>
{{#if cart.length}}
  <ul>
    {{#each cart}}
      <li>{{productId.name}} - Quantity: {{quantity}}</li>
    {{/each}}
  </ul>
  <p>Total: ${{cart.reduce (accumulator, item) => accumulator + item.productId.price * item.quantity, 0}}</p>
  <form action="/confirm-order" method="post">
    <button type="submit">Confirm Order</button>
  </form>
{{else}}
  <p>Your cart is empty.</p>
{{/if}}
router.get('/checkout', authMiddleware.ensureAuthenticated, orderController.getCheckoutPage);
router.post('/confirm-order', authMiddleware.ensureAuthenticated, orderController.postConfirmOrder);
exports.getCheckoutPage = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.items.productId');
    res.render('checkout', { cart: user.cart.items });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.postConfirmOrder = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.items.productId');
    const cartProducts = user.cart.items.map(item => ({
      quantity: item.quantity,
      product: { ...item.productId._doc }
    }));

    // Handle order confirmation logic, such as creating an order, updating inventory, etc.
    // For simplicity, we'll just add the products to the user's order history here.
    await user.addToOrderHistory(cartProducts);

    // Clear the user's cart after successful order confirmation
    user.cart = { items: [] };
    await user.save();

    // Notify the user about the order confirmation
    user.notifications.push('Your order has been confirmed! Thank you for shopping with us.');
    await user.save();

    res.redirect('/order-confirmed'); // Redirect to a confirmation page
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Cart view -->
<h2>Your Shopping Cart</h2>
{{#if cart.length}}
  {{#each cart}}
    <div>
      <p>{{productId.name}} - Quantity: {{quantity}}</p>
      <a href="/remove-from-cart/{{productId._id}}">Remove</a>
    </div>
  {{/each}}
  <p>Total: ${{cart.reduce (accumulator, item) => accumulator + item.productId.price * item.quantity, 0}}</p>
  <a href="/checkout">Proceed to Checkout</a>
{{else}}
  <p>Your cart is empty.</p>
{{/if}}
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/add-to-cart/:id', authMiddleware.ensureAuthenticated, cartController.addToCart);
router.get('/remove-from-cart/:id', authMiddleware.ensureAuthenticated, cartController.removeFromCart);
router.get('/cart', authMiddleware.ensureAuthenticated, cartController.getCartPage);
exports.addToCart = async (req, res) => {
  const productId = req.params.id;

  try {
    const product = await Product.findById(productId);

    if (!product) {
      return res.redirect('/');
    }

    const user = await User.findById(req.user._id);
    user.addToCart(product);

    res.redirect('/cart');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.removeFromCart = async (req, res) => {
  const productId = req.params.id;

  try {
    const user = await User.findById(req.user._id);
    user.removeFromCart(productId);

    res.redirect('/cart');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.getCartPage = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.items.productId');
    res.render('cart', { cart: user.cart.items });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Search Results view -->
<h2>Search Results for "{{query}}"</h2>
{{#if products.length}}
  <ul>
    {{#each products}}
      <li>{{this.name}} - {{this.description}} - ${{this.price}}</li>
    {{/each}}
  </ul>
{{else}}
  <p>No results found for "{{query}}".</p>
{{/if}}
router.get('/search', productController.searchProducts);
exports.searchProducts = async (req, res) => {
  const { query } = req.query;

  try {
    const products = await Product.find({
      $or: [
        { name: { $regex: new RegExp(query, 'i') } },
        { description: { $regex: new RegExp(query, 'i') } },
      ],
    });
    res.render('search-results', { query, products });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- User Profile view -->
<h2>User Profile</h2>
<p>Name: {{user.name}}</p>
<p>Email: {{user.email}}</p>
<p>Account Created: {{user.createdAt}}</p>
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/user-profile', authMiddleware.ensureAuthenticated, userController.getUserProfile);
exports.getUserProfile = async (req, res) => {
  try {
    const user = await User.findById(req.user._id);
    res.render('user-profile', { user });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Product Details view -->
<h2>{{product.name}}</h2>
<p>{{product.description}}</p>
<p>Price: ${{product.price}}</p>
<img src="{{product.imageUrl}}" alt="{{product.name}}">
router.get('/product-details/:id', productController.getProductDetailsPage);
exports.getProductDetailsPage = async (req, res) => {
  const productId = req.params.id;

  try {
    const product = await Product.findById(productId);
    res.render('product-details', { product });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Edit Product view -->
<h2>Edit Product</h2>
<form action="/edit-product/{{product._id}}" method="post">
  <label for="name">Name:</label>
  <input type="text" id="name" name="name" value="{{product.name}}" required>
  <label for="description">Description:</label>
  <textarea id="description" name="description" required>{{product.description}}</textarea>
  <label for="price">Price:</label>
  <input type="number" id="price" name="price" step="0.01" value="{{product.price}}" required>
  <label for="imageUrl">Image URL:</label>
  <input type="text" id="imageUrl" name="imageUrl" value="{{product.imageUrl}}" required>
  <button type="submit">Save Changes</button>
</form>
<!-- Add Product view -->
<h2>Add New Product</h2>
<form action="/add-product" method="post">
  <label for="name">Name:</label>
  <input type="text" id="name" name="name" required>
  <label for="description">Description:</label>
  <textarea id="description" name="description" required></textarea>
  <label for="price">Price:</label>
  <input type="number" id="price" name="price" step="0.01" required>
  <label for="imageUrl">Image URL:</label>
  <input type="text" id="imageUrl" name="imageUrl" required>
  <button type="submit">Add Product</button>
</form>
<!-- Manage Products view -->
<h2>Manage Products</h2>
<ul>
  {{#each products}}
    <li>
      {{this.name}} - {{this.description}} - ${{this.price}}
      <a href="/edit-product/{{this._id}}">Edit</a>
      <form action="/delete-product/{{this._id}}" method="post" onsubmit="return confirm('Are you sure?')">
        <button type="submit">Delete</button>
      </form>
    </li>
  {{/each}}
</ul>
<a href="/add-product">Add New Product</a>
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/manage-products', authMiddleware.isAdmin, adminController.getManageProductsPage);
router.get('/add-product', authMiddleware.isAdmin, adminController.getAddProductPage);
router.post('/add-product', authMiddleware.isAdmin, adminController.postAddProduct);
router.get('/edit-product/:id', authMiddleware.isAdmin, adminController.getEditProductPage);
router.post('/edit-product/:id', authMiddleware.isAdmin, adminController.postEditProduct);
router.post('/delete-product/:id', authMiddleware.isAdmin, adminController.postDeleteProduct);
exports.getManageProductsPage = async (req, res) => {
  try {
    const products = await Product.find();
    res.render('manage-products', { products });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.getAddProductPage = (req, res) => {
  res.render('add-product');
};

exports.postAddProduct = async (req, res) => {
  const { name, description, price, imageUrl } = req.body;

  try {
    const newProduct = new Product({
      name,
      description,
      price,
      imageUrl,
    });

    await newProduct.save();
    res.redirect('/manage-products');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.getEditProductPage = async (req, res) => {
  const productId = req.params.id;

  try {
    const product = await Product.findById(productId);
    res.render('edit-product', { product });
  } catch (err) {
    console.error(err);
    res.redirect('/manage-products'); // Handle error
  }
};

exports.postEditProduct = async (req, res) => {
  const productId = req.params.id;
  const { name, description, price, imageUrl } = req.body;

  try {
    const product = await Product.findById(productId);
    product.name = name;
    product.description = description;
    product.price = price;
    product.imageUrl = imageUrl;

    await product.save();
    res.redirect('/manage-products');
  } catch (err) {
    console.error(err);
    res.redirect('/manage-products'); // Handle error
  }
};

exports.postDeleteProduct = async (req, res) => {
  const productId = req.params.id;

  try {
    await Product.findByIdAndDelete(productId);
    res.redirect('/manage-products');
  } catch (err) {
    console.error(err);
    res.redirect('/manage-products'); // Handle error
  }
};
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/checkout', authMiddleware.ensureAuthenticated, orderController.getCheckoutPage);
router.post('/confirm-order', authMiddleware.ensureAuthenticated, orderController.postConfirmOrder);
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/cart', authMiddleware.ensureAuthenticated, cartController.getCartPage);
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/user-profile', authMiddleware.ensureAuthenticated, userController.getUserProfile);
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/admin-panel', authMiddleware.isAdmin, adminController.getAdminPanel);
exports.ensureAuthenticated = (req, res, next) => {
  if (req.isAuthenticated()) {
    return next();
  }

  res.redirect('/login');
};

exports.isAdmin = (req, res, next) => {
  if (req.isAuthenticated() && req.user.isAdmin) {
    return next();
  }

  res.redirect('/'); // Redirect unauthorized users to the home page
};
exports.postConfirmOrder = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.items.productId');
    const cartProducts = user.cart.items.map(item => ({
      quantity: item.quantity,
      product: { ...item.productId._doc }
    }));

    // Handle order confirmation logic, such as creating an order, updating inventory, etc.
    // For simplicity, we'll just add the products to the user's order history here.
    await user.addToOrderHistory(cartProducts);

    // Clear the user's cart after successful order confirmation
    user.cart = { items: [] };
    await user.save();

    // Send order confirmation email
    const transporter = req.app.get('transporter');
    const mailOptions = {
      from: 'your.email@gmail.com',
      to: user.email,
      subject: 'Order Confirmation',
      html: `<p>Your order has been confirmed. Thank you for shopping with us!</p>`,
    };

    transporter.sendMail(mailOptions, (error, info) => {
      if (error) {
        console.error(error);
        // Handle email sending error
      } else {
        console.log('Email sent: ' + info.response);
      }
    });

    // Notify the user about the order confirmation
    user.notifications.push('Your order has been confirmed! Thank you for shopping with us.');
    await user.save();

    res.redirect('/order-confirmed'); // Redirect to a confirmation page
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
const nodemailer = require('nodemailer');

// ... (existing app configuration)

// Nodemailer setup
const transporter = nodemailer.createTransport({
  service: 'gmail',
  auth: {
    user: 'your.email@gmail.com',
    pass: 'your-email-password',
  },
});

app.set('transporter', transporter);

// ... (existing server setup)
npm install nodemailer
exports.getChatPage = (req, res) => {
  res.render('chat');
};
router.get('/chat', authMiddleware.ensureAuthenticated, chatController.getChatPage);
<!-- Chat view -->
<h2>Real-time Chat</h2>
<div id="chat-box"></div>
<form id="chat-form">
  <input type="text" id="message-input" placeholder="Type your message...">
  <button type="submit">Send</button>
</form>

<script src="https://cdnjs.cloudflare.com/ajax/libs/socket.io/4.0.1/socket.io.js"></script>
<script>
  const socket = io();

  // Listen for incoming chat messages
  socket.on('chatMessage', message => {
    const chatBox = document.getElementById('chat-box');
    chatBox.innerHTML += `<p>${message}</p>`;
  });

  // Handle form submission to send chat messages
  document.getElementById('chat-form').addEventListener('submit', event => {
    event.preventDefault();
    const messageInput = document.getElementById('message-input');
    const message = messageInput.value.trim();

    if (message) {
      socket.emit('chatMessage', message);
      messageInput.value = '';
    }
  });
</script>
const express = require('express');
const http = require('http');
const socketIO = require('socket.io');

const app = express();
const server = http.createServer(app);
const io = socketIO(server);

// ... (existing app configuration)

// Socket.io setup
io.on('connection', socket => {
  console.log('A user connected');

  // Handle chat messages
  socket.on('chatMessage', message => {
    io.emit('chatMessage', message); // Broadcast the message to all connected users
  });

  // Handle disconnect
  socket.on('disconnect', () => {
    console.log('A user disconnected');
  });
});

// ... (existing server setup)
npm install socket.io
<!-- Order Confirmed view -->
<h2>Order Confirmed</h2>
<p>Your order has been confirmed. Thank you for shopping with us!</p>
<!-- Checkout view -->
<h2>Review Your Order</h2>
{{#if cart.length}}
  <ul>
    {{#each cart}}
      <li>{{productId.name}} - Quantity: {{quantity}}</li>
    {{/each}}
  </ul>
  <p>Total: ${{cart.reduce (accumulator, item) => accumulator + item.productId.price * item.quantity, 0}}</p>
  <form action="/confirm-order" method="post">
    <button type="submit">Confirm Order</button>
  </form>
{{else}}
  <p>Your cart is empty.</p>
{{/if}}
router.get('/checkout', authMiddleware.ensureAuthenticated, orderController.getCheckoutPage);
router.post('/confirm-order', authMiddleware.ensureAuthenticated, orderController.postConfirmOrder);
exports.getCheckoutPage = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.items.productId');
    res.render('checkout', { cart: user.cart.items });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.postConfirmOrder = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.items.productId');
    const cartProducts = user.cart.items.map(item => ({
      quantity: item.quantity,
      product: { ...item.productId._doc }
    }));

    // Handle order confirmation logic, such as creating an order, updating inventory, etc.
    // For simplicity, we'll just add the products to the user's order history here.
    await user.addToOrderHistory(cartProducts);

    // Clear the user's cart after successful order confirmation
    user.cart = { items: [] };
    await user.save();

    // Notify the user about the order confirmation
    user.notifications.push('Your order has been confirmed! Thank you for shopping with us.');
    await user.save();

    res.redirect('/order-confirmed'); // Redirect to a confirmation page
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Cart view -->
<h2>Your Shopping Cart</h2>
{{#if cart.length}}
  {{#each cart}}
    <div>
      <p>{{productId.name}} - Quantity: {{quantity}}</p>
      <a href="/remove-from-cart/{{productId._id}}">Remove</a>
    </div>
  {{/each}}
  <p>Total: ${{cart.reduce (accumulator, item) => accumulator + item.productId.price * item.quantity, 0}}</p>
  <a href="/checkout">Proceed to Checkout</a>
{{else}}
  <p>Your cart is empty.</p>
{{/if}}
router.get('/cart', authMiddleware.ensureAuthenticated, cartController.getCartPage);
exports.getCartPage = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.items.productId');
    res.render('cart', { cart: user.cart.items });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Navbar partial -->
<nav>
  <ul>
    <li><a href="/">Home</a></li>
    <li><a href="/products">Products</a></li>
    {{#if user}}
      <li><a href="/user-profile">Profile</a></li>
      <li><a href="/cart">Cart</a></li> <!-- New line for the shopping cart -->
      <li><a href="/logout">Logout</a></li>
    {{else}}
      <li><a href="/login">Login</a></li>
      <li><a href="/register">Register</a></li>
    {{/if}}
  </ul>
</nav>
<!-- Product Listing view -->
<h2>Product Listing</h2>
<ul>
  {{#each products}}
    <li>{{this.name}} - {{this.description}} - ${{this.price}}</li>
  {{/each}}
</ul>
<div class="pagination">
  {{#if hasPrevPage}}
    <a href="/products?page={{prevPage}}">&laquo; Previous</a>
  {{/if}}
  {{#if hasNextPage}}
    <a href="/products?page={{nextPage}}">Next &raquo;</a>
  {{/if}}
</div>
router.get('/products', productController.getPaginatedProducts);
const ITEMS_PER_PAGE = 10;

exports.getPaginatedProducts = async (req, res) => {
  const page = +req.query.page || 1;

  try {
    const totalProducts = await Product.countDocuments();
    const products = await Product.find()
      .skip((page - 1) * ITEMS_PER_PAGE)
      .limit(ITEMS_PER_PAGE);

    res.render('product-listing', {
      products,
      currentPage: page,
      hasNextPage: ITEMS_PER_PAGE * page < totalProducts,
      hasPrevPage: page > 1,
      nextPage: page + 1,
      prevPage: page - 1,
      lastPage: Math.ceil(totalProducts / ITEMS_PER_PAGE),
    });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Search Results view -->
<h2>Search Results for "{{query}}"</h2>
{{#if products.length}}
  <ul>
    {{#each products}}
      <li>{{this.name}} - {{this.description}} - ${{this.price}}</li>
    {{/each}}
  </ul>
{{else}}
  <p>No results found for "{{query}}".</p>
{{/if}}
router.get('/search', productController.searchProducts);
exports.searchProducts = async (req, res) => {
  const { query } = req.query;

  try {
    const products = await Product.find({
      $or: [
        { name: { $regex: new RegExp(query, 'i') } },
        { description: { $regex: new RegExp(query, 'i') } },
      ],
    });
    res.render('search-results', { query, products });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- User Profile view -->
<h2>Your Profile</h2>
<p>Username: {{user.username}}</p>
<p>Email: {{user.email}}</p>
<h3>Order History</h3>
{{#if user.orders.length}}
  {{#each user.orders}}
    <div>
      {{#each this.items}}
        <p>{{product.name}} - Quantity: {{quantity}}</p>
      {{/each}}
    </div>
  {{/each}}
{{else}}
  <p>No order history available.</p>
{{/if}}
router.get('/user-profile', authMiddleware.ensureAuthenticated, userController.getUserProfile);
exports.getUserProfile = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('orders');
    res.render('user-profile', { user });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Product Details with Reviews view -->
<h2>{{product.name}}</h2>
<p>{{product.description}}</p>
<p>Price: ${{product.price}}</p>
<img src="{{product.imageUrl}}" alt="{{product.name}}">
<h3>Reviews</h3>
{{#if product.reviews.length}}
  <ul>
    {{#each product.reviews}}
      <li>{{this.user.username}} says: {{this.text}}</li>
    {{/each}}
  </ul>
{{else}}
  <p>No reviews yet. Be the first to leave a review!</p>
{{/if}}
<form action="/product-reviews/{{product._id}}" method="post">
  <label for="reviewText">Leave a Review:</label>
  <textarea id="reviewText" name="reviewText" required></textarea>
  <button type="submit">Submit Review</button>
</form>
router.get('/product-details-reviews/:id', productController.getProductDetailsWithReviews);
exports.getProductDetailsWithReviews = async (req, res) => {
  const productId = req.params.id;

  try {
    const product = await Product.findById(productId).populate('reviews.user');
    res.render('product-details-reviews', { product });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Password Reset Sent view -->
<h2>Password Reset Sent</h2>
<p>An email with instructions to reset your password has been sent to your email address. Please check your inbox.</p>
exports.getPasswordResetSent = (req, res) => {
  res.render('password-reset-sent');
};
<!-- Forgot Password view -->
<h2>Forgot Password</h2>
<form action="/forgot-password" method="post">
  <label for="email">Email:</label>
  <input type="email" id="email" name="email" required>
  <button type="submit">Reset Password</button>
</form>
router.get('/forgot-password', authController.getForgotPassword);
router.post('/forgot-password', authController.postForgotPassword);
const crypto = require('crypto');

exports.getForgotPassword = (req, res) => {
  res.render('forgot-password');
};

exports.postForgotPassword = async (req, res) => {
  const { email } = req.body;

  try {
    const user = await User.findOne({ email });

    if (!user) {
      req.flash('error_msg', 'No account with that email address exists.');
      return res.redirect('/forgot-password');
    }

    // Generate a reset token and set its expiration time
    user.resetToken = crypto.randomBytes(32).toString('hex');
    user.resetTokenExpiration = Date.now() + 3600000; // Token expires in 1 hour

    await user.save();

    // Send the reset token to the user's email (you would use a service like Nodemailer for this)
    // ...

    res.redirect('/password-reset-sent'); // Redirect to a confirmation page
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Admin Panel view -->
<h2>Admin Panel</h2>
<h3>Product Management</h3>
<ul>
  {{#each products}}
    <li>{{this.name}} - {{this.description}} - ${{this.price}}</li>
  {{/each}}
</ul>
<h3>User Management</h3>
<ul>
  {{#each users}}
    <li>{{this.username}} - {{this.email}}</li>
  {{/each}}
</ul>
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/admin-panel', authMiddleware.isAdmin, adminController.getAdminPanel);
exports.getAdminPanel = async (req, res) => {
  try {
    const products = await Product.find();
    const users = await User.find();
    res.render('admin-panel', { products, users });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Product Reviews view -->
<h2>Product Reviews - {{product.name}}</h2>
{{#if product.reviews.length}}
  <ul>
    {{#each product.reviews}}
      <li>{{this.user.username}} says: {{this.text}}</li>
    {{/each}}
  </ul>
{{else}}
  <p>No reviews yet. Be the first to leave a review!</p>
{{/if}}
<form action="/product-reviews/{{product._id}}" method="post">
  <label for="reviewText">Leave a Review:</label>
  <textarea id="reviewText" name="reviewText" required></textarea>
  <button type="submit">Submit Review</button>
</form>
router.get('/product-reviews/:id', authMiddleware.ensureAuthenticated, productController.getProductReviews);
router.post('/product-reviews/:id', authMiddleware.ensureAuthenticated, productController.postProductReview);
exports.getProductReviews = async (req, res) => {
  const productId = req.params.id;

  try {
    const product = await Product.findById(productId).populate('reviews.user');
    res.render('product-reviews', { product });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.postProductReview = async (req, res) => {
  const productId = req.params.id;
  const { reviewText } = req.body;

  try {
    const product = await Product.findById(productId);
    product.reviews.push({ user: req.user._id, text: reviewText });
    await product.save();
    res.redirect(`/product-reviews/${productId}`);
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
const mongoose = require('mongoose');

const productSchema = new mongoose.Schema({
  name: { type: String, required: true },
  description: { type: String, required: true },
  price: { type: Number, required: true },
  imageUrl: { type: String, required: true },
  rating: { type: Number, default: 0 },
  reviews: [{ user: { type: mongoose.Schema.Types.ObjectId, ref: 'User' }, text: String }],
  // ... other fields like inventory, etc.
});

const Product = mongoose.model('Product', productSchema);

module.exports = Product;
<!-- Dashboard view -->
<h2>Your Dashboard</h2>
<p>Welcome, {{user.username}}!</p>
<h3>Order History</h3>
{{#if user.orders.length}}
  {{#each user.orders}}
    <div>
      {{#each this.items}}
        <p>{{product.name}} - Quantity: {{quantity}}</p>
      {{/each}}
    </div>
  {{/each}}
{{else}}
  <p>No order history available.</p>
{{/if}}
router.get('/dashboard', authMiddleware.ensureAuthenticated, userController.getDashboard);
exports.getDashboard = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('orders');
    res.render('dashboard', { user });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Order Success view -->
<h2>Your Order was Successful!</h2>
<p>Thank you for shopping with us. Your order will be processed shortly.</p>
router.get('/process-order', authMiddleware.ensureAuthenticated, orderController.processOrder);
exports.processOrder = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.items.productId');
    const cartProducts = user.cart.items.map(item => ({
      quantity: item.quantity,
      product: { ...item.productId._doc }
    }));

    // Handle order processing logic, such as creating an order, updating inventory, etc.
    // For simplicity, we'll just add the products to the user's order history here.
    await user.addToOrderHistory(cartProducts);

    // Clear the user's cart after successful order processing
    user.cart = { items: [] };
    await user.save();

    // Notify the user about the order
    user.notifications.push('Your order has been processed successfully!');
    await user.save();

    res.redirect('/order-success'); // Redirect to a success page
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Notifications view -->
<h2>Your Notifications</h2>
{{#if notifications.length}}
  <ul>
    {{#each notifications}}
      <li>{{this}}</li>
    {{/each}}
  </ul>
{{else}}
  <p>No notifications yet.</p>
{{/if}}
router.get('/notifications', authMiddleware.ensureAuthenticated, notificationController.getNotifications);
exports.getNotifications = async (req, res) => {
  try {
    const user = await User.findById(req.user._id);
    const notifications = user.notifications;
    res.render('notifications', { notifications });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Chat view -->
<h2>Real-time Chat</h2>
<div id="chat-container">
  <ul id="chat-messages"></ul>
</div>
<form id="chat-form" action="/chat" method="post">
  <input type="text" id="message" name="message" placeholder="Type your message" required>
  <button type="submit">Send</button>
</form>

<script src="/socket.io/socket.io.js"></script>
<script>
  const socket = io();

  const chatForm = document.getElementById('chat-form');
  const chatMessages = document.getElementById('chat-messages');

  chatForm.addEventListener('submit', (e) => {
    e.preventDefault();
    const messageInput = document.getElementById('message');
    const message = messageInput.value;
    socket.emit('chatMessage', { user: '{{user.username}}', message });
    messageInput.value = '';
  });

  socket.on('chatMessage', (data) => {
    const li = document.createElement('li');
    li.textContent = `${data.user}: ${data.message}`;
    chatMessages.appendChild(li);
  });
</script>
router.get('/chat', authMiddleware.ensureAuthenticated, chatController.getChat);
router.post('/chat', authMiddleware.ensureAuthenticated, chatController.postChatMessage);
const io = require('../socket');

exports.getChat = (req, res) => {
  res.render('chat');
};

exports.postChatMessage = (req, res) => {
  const { message } = req.body;
  io.getIO().emit('chatMessage', {
    user: req.user.username,
    message: message,
  });
  res.status(200).json({ message: 'Message sent successfully.' });
};
router.get('/cart', authMiddleware.ensureAuthenticated, cartController.getCart);
router.get('/add-to-cart/:id', authMiddleware.ensureAuthenticated, cartController.addToCart);
router.get('/remove-from-cart/:id', authMiddleware.ensureAuthenticated, cartController.removeFromCart);
<!-- Cart view -->
<h2>Your Shopping Cart</h2>
{{#if cart.length}}
  {{#each cart}}
    <div>
      <p>{{productId.name}} - Quantity: {{quantity}}</p>
      <a href="/remove-from-cart/{{productId._id}}">Remove</a>
    </div>
  {{/each}}
  <p>Total: ${{cart.reduce (accumulator, item) => accumulator + item.productId.price * item.quantity, 0}}</p>
  <a href="/checkout">Proceed to Checkout</a>
{{else}}
  <p>Your cart is empty.</p>
{{/if}}
exports.addToCart = async (req, res) => {
  const productId = req.params.id;

  try {
    const product = await Product.findById(productId);
    req.user.addToCart(product);
    res.redirect('/cart');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.removeFromCart = async (req, res) => {
  const productId = req.params.id;

  try {
    await req.user.removeFromCart(productId);
    res.redirect('/cart');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.getCart = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.items.productId');
    res.render('cart', { cart: user.cart.items });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Products view -->
<h2>Products</h2>
{{#each products}}
  <div>
    <p>{{name}} - {{description}} - ${{price}} - Rating: {{rating}}</p>
    <form action="/rate-product/{{_id}}" method="post">
      <label for="rating">Rate this product:</label>
      <input type="number" id="rating" name="rating" min="1" max="5" step="0.1" required>
      <button type="submit">Submit Rating</button>
    </form>
    <a href="/edit-product/{{_id}}">Edit</a>
    <a href="/delete-product/{{_id}}">Delete</a>
  </div>
{{/each}}
router.post('/rate-product/:id', authMiddleware.ensureAuthenticated, productController.rateProduct);
exports.rateProduct = async (req, res) => {
  const productId = req.params.id;
  const { rating } = req.body;

  try {
    const product = await Product.findById(productId);
    product.rating = (product.rating + parseFloat(rating)) / 2;
    await product.save();
    res.redirect('/products');
  } catch (err) {
    console.error(err);
    res.redirect('/products'); // Handle error
  }
};
const mongoose = require('mongoose');

const productSchema = new mongoose.Schema({
  name: { type: String, required: true },
  description: { type: String, required: true },
  price: { type: Number, required: true },
  imageUrl: { type: String, required: true },
  rating: { type: Number, default: 0 },
  // ... other fields like reviews, inventory, etc.
});

const Product = mongoose.model('Product', productSchema);

module.exports = Product;
const authMiddleware = require('../middlewares/authMiddleware');

router.get('/create-product', authMiddleware.isAdmin, productController.createProductForm);
router.post('/create-product', authMiddleware.isAdmin, productController.createProduct);
router.get('/edit-product/:id', authMiddleware.isAdmin, productController.editProductForm);
router.post('/edit-product/:id', authMiddleware.isAdmin, productController.editProduct);
router.get('/delete-product/:id', authMiddleware.isAdmin, productController.deleteProduct);
module.exports = {
  ensureAuthenticated: (req, res, next) => {
    if (req.isAuthenticated()) {
      return next();
    }
    req.flash('error_msg', 'Please log in to view this resource.');
    res.redirect('/login');
  },

  isAdmin: (req, res, next) => {
    // Assuming you have a 'role' field in your user model
    if (req.isAuthenticated() && req.user.role === 'admin') {
      return next();
    }
    req.flash('error_msg', 'You do not have permission to access this resource.');
    res.redirect('/');
  },
};
<!-- Product Details view -->
<h2>{{product.name}}</h2>
<p>{{product.description}}</p>
<p>${{product.price}}</p>
<img src="{{product.imageUrl}}" alt="{{product.name}}">
exports.getProductDetails = async (req, res) => {
  const productId = req.params.id;

  try {
    const product = await Product.findById(productId);
    res.render('product-details', { product });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Products view -->
<h2>Products</h2>
{{#each products}}
  <div>
    <p>{{name}} - {{description}} - ${{price}}</p>
    <a href="/edit-product/{{_id}}">Edit</a>
    <a href="/delete-product/{{_id}}">Delete</a>
  </div>
{{/each}}
<!-- Edit Product view -->
<h2>Edit Product</h2>
<form action="/edit-product/{{product._id}}" method="post">
  <label for="name">Name:</label>
  <input type="text" id="name" name="name" value="{{product.name}}" required>
  <br>
  <label for="description">Description:</label>
  <textarea id="description" name="description" required>{{product.description}}</textarea>
  <br>
  <label for="price">Price:</label>
  <input type="number" id="price" name="price" value="{{product.price}}" required>
  <br>
  <label for="imageUrl">Image URL:</label>
  <input type="url" id="imageUrl" name="imageUrl" value="{{product.imageUrl}}" required>
  <br>
  <button type="submit">Save Changes</button>
</form>
<!-- Create Product view -->
<h2>Create Product</h2>
<form action="/create-product" method="post">
  <label for="name">Name:</label>
  <input type="text" id="name" name="name" required>
  <br>
  <label for="description">Description:</label>
  <textarea id="description" name="description" required></textarea>
  <br>
  <label for="price">Price:</label>
  <input type="number" id="price" name="price" required>
  <br>
  <label for="imageUrl">Image URL:</label>
  <input type="url" id="imageUrl" name="imageUrl" required>
  <br>
  <button type="submit">Create Product</button>
</form>
router.get('/create-product', productController.createProductForm);
router.post('/create-product', productController.createProduct);
router.get('/edit-product/:id', productController.editProductForm);
router.post('/edit-product/:id', productController.editProduct);
router.get('/delete-product/:id', productController.deleteProduct);
const flash = require('connect-flash');
app.use(flash());
app.use((req, res, next) => {
  res.locals.success_msg = req.flash('success_msg');
  res.locals.error_msg = req.flash('error_msg');
  res.locals.error = req.flash('error');
  next();
});
// ... (existing code)

exports.createProductForm = (req, res) => {
  res.render('create-product');
};

exports.createProduct = async (req, res) => {
  const { name, description, price, imageUrl } = req.body;

  try {
    const product = await Product.create({ name, description, price, imageUrl });
    res.redirect('/products');
  } catch (err) {
    console.error(err);
    res.redirect('/create-product'); // Handle error
  }
};

exports.editProductForm = async (req, res) => {
  const productId = req.params.id;

  try {
    const product = await Product.findById(productId);
    res.render('edit-product', { product });
  } catch (err) {
    console.error(err);
    res.redirect('/products'); // Handle error
  }
};

exports.editProduct = async (req, res) => {
  const productId = req.params.id;
  const { name, description, price, imageUrl } = req.body;

  try {
    await Product.findByIdAndUpdate(productId, { name, description, price, imageUrl });
    res.redirect('/products');
  } catch (err) {
    console.error(err);
    res.redirect('/products'); // Handle error
  }
};

exports.deleteProduct = async (req, res) => {
  const productId = req.params.id;

  try {
    await Product.findByIdAndRemove(productId);
    res.redirect('/products');
  } catch (err) {
    console.error(err);
    res.redirect('/products'); // Handle error
  }
};
exports.logout = (req, res) => {
  req.logout();
  req.flash('success_msg', 'You have been logged out.');
  res.redirect('/');
};
<!-- Search view -->
<h2>Search Results for "{{searchTerm}}"</h2>
{{#if products.length}}
  {{#each products}}
    <div>
      <p>{{name}} - {{description}}</p>
    </div>
  {{/each}}
{{else}}
  <p>No results found.</p>
{{/if}}
router.get('/search', productController.searchProducts);
exports.searchProducts = async (req, res) => {
  const searchTerm = req.query.q;

  try {
    const products = await Product.find({
      $text: { $search: searchTerm },
    });

    res.render('search', { products, searchTerm });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
router.get('/profile', authMiddleware.ensureAuthenticated, userController.getProfile);
router.post('/profile/update', authMiddleware.ensureAuthenticated, userController.updateProfile);
<!-- Profile view -->
<h2>Your Profile</h2>
<p>Username: {{user.username}}</p>
<p>Email: {{user.email}}</p>

<h3>Favorites</h3>
{{#if user.favorites.length}}
  {{#each user.favorites}}
    <div>
      <p>{{name}} - {{description}}</p>
    </div>
  {{/each}}
{{else}}
  <p>No favorites yet.</p>
{{/if}}

<form action="/profile/update" method="post">
  <label for="username">Update Username:</label>
  <input type="text" id="username" name="username" required>
  <br>
  <label for="email">Update Email:</label>
  <input type="email" id="email" name="email" required>
  <br>
  <button type="submit">Update Profile</button>
</form>
exports.getProfile = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('favorites');
    res.render('profile', { user });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.updateProfile = async (req, res) => {
  const { username, email } = req.body;

  try {
    const user = await User.findById(req.user._id);
    user.username = username;
    user.email = email;
    await user.save();

    res.redirect('/profile');
  } catch (err) {
    console.error(err);
    res.redirect('/profile'); // Handle error
  }
};
<!-- Order History view -->
<h2>Order History</h2>
{{#if orders.length}}
  {{#each orders}}
    <div>
      {{#each this.items}}
        <p>{{product.name}} - Quantity: {{quantity}}</p>
      {{/each}}
    </div>
  {{/each}}
{{else}}
  <p>No order history available.</p>
{{/if}}
router.get('/order-history', authMiddleware.ensureAuthenticated, userController.getOrderHistory);
userSchema.methods.addToOrderHistory = function (products) {
  this.orders.push({ items: products });
  return this.save();
};
exports.getOrderHistory = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('orders');
    res.render('order-history', { orders: user.orders });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
<!-- Checkout view -->
{{#if cartProducts.length}}
  <h2>Checkout</h2>
  <form action="/checkout" method="post">
    {{#each cartProducts}}
      <div>
        <p>{{product.name}} - Quantity: {{quantity}}</p>
      </div>
    {{/each}}
    <button type="submit">Place Order</button>
  </form>
{{else}}
  <p>Your cart is empty.</p>
{{/if}}
exports.getCheckout = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.items.productId');
    const cartProducts = user.cart.items.map(item => ({
      product: { ...item.productId._doc },
      quantity: item.quantity
    }));
    res.render('checkout', { cartProducts });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.postCheckout = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.items.productId');
    const cartProducts = user.cart.items.map(item => ({
      quantity: item.quantity,
      product: { ...item.productId._doc }
    }));

    // Handle the checkout logic, such as creating an order, processing payment, etc.
    // You would typically integrate with a payment gateway for this.

    // Clear the user's cart after successful checkout
    user.cart = { items: [] };
    await user.save();

    res.redirect('/order-success'); // Redirect to a success page
  } catch (err) {
    console.error(err);
    res.redirect('/checkout'); // Handle error
  }
};
// ... (existing code)

userSchema.methods.addToCart = function (productId) {
  const cartProductIndex = this.cart.items.findIndex((cp) => {
    return cp.productId.toString() === productId.toString();
  });

  let newQuantity = 1;
  const updatedCartItems = [...this.cart.items];

  if (cartProductIndex >= 0) {
    newQuantity = this.cart.items[cartProductIndex].quantity + 1;
    updatedCartItems[cartProductIndex].quantity = newQuantity;
  } else {
    updatedCartItems.push({
      productId: productId,
      quantity: newQuantity,
    });
  }

  this.cart = { items: updatedCartItems };
  return this.save();
};

userSchema.methods.removeFromCart = function (productId) {
  const updatedCartItems = this.cart.items.filter(item => {
    return item.productId.toString() !== productId.toString();
  });

  this.cart.items = updatedCartItems;
  return this.save();
};
exports.getCart = async (req, res) => {
  try {
    const user = await User.findById(req.user._id).populate('cart.items.productId');
    res.render('cart', { cart: user.cart.items });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.addToCart = async (req, res) => {
  const productId = req.params.id;

  try {
    // Add product to user's cart
    const user = req.user;
    await user.addToCart(productId);

    res.redirect('/cart');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.removeFromCart = async (req, res) => {
  const productId = req.params.id;

  try {
    // Remove product from user's cart
    const user = req.user;
    await user.removeFromCart(productId);

    res.redirect('/cart');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
const Product = require('../models/Product');

exports.browseProducts = async (req, res) => {
  try {
    const products = await Product.find();
    res.render('browse', { products });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.getProductDetails = async (req, res) => {
  const productId = req.params.id;
  
  try {
    const product = await Product.findById(productId);
    res.render('product-details', { product });
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};

exports.addToFavorites = async (req, res) => {
  const productId = req.params.id;

  try {
    // Add product to user's favorites
    const user = req.user;
    user.favorites.push(productId);
    await user.save();

    res.redirect('/profile');
  } catch (err) {
    console.error(err);
    res.redirect('/'); // Handle error
  }
};
const mongoose = require('mongoose');

const productSchema = new mongoose.Schema({
  name: { type: String, required: true },
  description: { type: String, required: true },
  price: { type: Number, required: true },
  imageUrl: { type: String, required: true },
  // ... other fields like reviews, inventory, etc.
});

const Product = mongoose.model('Product', productSchema);

module.exports = Product;
exports.getLogin = (req, res) => {
  res.render('login');
};

exports.postLogin = passport.authenticate('local', {
  successRedirect: '/',
  failureRedirect: '/login',
  failureFlash: true,
});

exports.logout = (req, res) => {
  req.logout();
  res.redirect('/');
};

exports.getRegister = (req, res) => {
  res.render('register');
};

exports.postRegister = async (req, res) => {
  const { username, password, email } = req.body;

  try {
    const user = await User.create({ username, password, email });
    req.login(user, (err) => {
      if (err) return next(err);
      res.redirect('/');
    });
  } catch (err) {
    console.error(err);
    res.redirect('/register'); // Handle registration failure
  }
};
const express = require('express');
const passport = require('passport');
const authController = require('../controllers/authController');

const router = express.Router();

router.get('/login', authController.getLogin);

router.post('/login', passport.authenticate('local', {
  successRedirect: '/',
  failureRedirect: '/login',
  failureFlash: true,
}));

router.get('/logout', authController.logout);

router.get('/register', authController.getRegister);

router.post('/register', authController.postRegister);

module.exports = router;
const mongoose = require('mongoose');
const bcrypt = require('bcrypt');

const userSchema = new mongoose.Schema({
  username: { type: String, required: true, unique: true },
  password: { type: String, required: true },
  email: { type: String, required: true, unique: true },
  // ... other fields like orders, address, etc.
});

userSchema.pre('save', function (next) {
  const user = this;

  if (!user.isModified('password')) return next();

  bcrypt.genSalt(10, (err, salt) => {
    if (err) return next(err);

    bcrypt.hash(user.password, salt, (err, hash) => {
      if (err) return next(err);

      user.password = hash;
      next();
    });
  });
});

userSchema.methods.comparePassword = function (candidatePassword) {
  return bcrypt.compare(candidatePassword, this.password);
};

const User = mongoose.model('User', userSchema);

module.exports = User;
const mongoose = require('mongoose');
const config = require('./config');

mongoose.connect(config.mongoURI, { useNewUrlParser: true, useUnifiedTopology: true });
const passport = require('passport');
const LocalStrategy = require('passport-local').Strategy;
const User = require('../models/User');

passport.use(new LocalStrategy(
  { usernameField: 'username', passwordField: 'password' },
  async (username, password, done) => {
    try {
      const user = await User.findOne({ username });

      if (!user) {
        return done(null, false, { message: 'Incorrect username.' });
      }

      const isMatch = await user.comparePassword(password);

      if (isMatch) {
        return done(null, user);
      } else {
        return done(null, false, { message: 'Incorrect password.' });
      }
    } catch (err) {
      return done(err);
    }
  }
));

passport.serializeUser((user, done) => {
  done(null, user.id);
});

passport.deserializeUser(async (id, done) => {
  try {
    const user = await User.findById(id);
    done(null, user);
  } catch (err) {
    done(err);
  }
});
// Main application file
<!-- Search view -->
<!-- Register view -->
<!-- Profile view -->
<!-- Product details view -->
<!-- Login view -->
<!-- Home view -->
<!-- Contact view -->
<!-- Checkout view -->
<!-- Cart view -->
<!-- Browse view -->
// User-related controller
// Product-related controller
// Checkout-related controller
// Cart-related controller
// Authentication controller
// User-related routes
// Product-related routes
// Checkout-related routes
// Cart-related routes
// Authentication routes
// Authentication middleware
// User model
// Product model
// Mongoose configuration
// Passport.js configuration
npm init -y
npm install express express-handlebars mongoose body-parser bcrypt passport passport-local express-session socket.io
const User = require('../models/User');
const Product = require('../models/Product');

exports.getProfile = async (req, res) => {
  const user = await User.findById(req.user._id).populate('favorites');
  res.render('profile', { user });
};

exports.updateProfile = async (req, res) => {
  // Update user profile logic
};

exports.getCart = async (req, res) => {
  // Fetch user's cart items and render the cart view
};

exports.addToCart = async (req, res) => {
  // Add product to user's cart
};

exports.removeFromCart = async (req, res) => {
  // Remove product from user's cart
};

exports.getCheckout = async (req, res) => {
  // Fetch user's cart items and render the checkout view
};

exports.postCheckout = async (req, res) => {
  // Process the checkout logic
};

exports.getContact = (req, res) => {
  res.render('contact');
};

exports.postContact = (req, res) => {
  // Handle contact form submission
};
const Product = require('../models/Product');

exports.browseProducts = async (req, res) => {
  const products = await Product.find();
  res.render('browse', { products });
};

exports.getProductDetails = async (req, res) => {
  const productId = req.params.id;
  const product = await Product.findById(productId);
  res.render('product-details', { product });
};

exports.addToFavorites = async (req, res) => {
  const productId = req.params.id;
  // Add product to user's favorites
};
const passport = require('passport');
const config = require('../config');

exports.getLogin = (req, res) => {
  res.render('login');
};

exports.postLogin = passport.authenticate('local', {
  successRedirect: '/',
  failureRedirect: '/login',
  failureFlash: true,
});

exports.logout = (req, res) => {
  req.logout();
  res.redirect('/');
};

exports.getRegister = (req, res) => {
  res.render('register');
};

exports.postRegister = (req, res) => {
  // Handle registration logic
};
const express = require('express');
const userController = require('../controllers/userController');
const authMiddleware = require('../middlewares/authMiddleware');

const router = express.Router();

router.get('/profile', authMiddleware.ensureAuthenticated, userController.getProfile);

router.post('/profile/update', authMiddleware.ensureAuthenticated, userController.updateProfile);

router.get('/cart', authMiddleware.ensureAuthenticated, userController.getCart);

router.post('/cart/add/:id', authMiddleware.ensureAuthenticated, userController.addToCart);

router.post('/cart/remove/:id', authMiddleware.ensureAuthenticated, userController.removeFromCart);

router.get('/checkout', authMiddleware.ensureAuthenticated, userController.getCheckout);

router.post('/checkout', authMiddleware.ensureAuthenticated, userController.postCheckout);

router.get('/contact', authMiddleware.ensureAuthenticated, userController.getContact);

router.post('/contact', authMiddleware.ensureAuthenticated, userController.postContact);

// ... add more routes as needed

module.exports = router;
const express = require('express');
const productController = require('../controllers/productController');

const router = express.Router();

router.get('/browse', productController.browseProducts);

router.get('/products/:id', productController.getProductDetails);

router.post('/products/:id/add-to-favorites', productController.addToFavorites);

// ... add more routes as needed

module.exports = router;
const express = require('express');
const passport = require('passport');
const authController = require('../controllers/authController');

const router = express.Router();

router.get('/login', authController.getLogin);

router.post('/login', passport.authenticate('local', {
  successRedirect: '/',
  failureRedirect: '/login',
  failureFlash: true,
}));

router.get('/logout', authController.logout);

router.get('/register', authController.getRegister);

router.post('/register', authController.postRegister);

module.exports = router;
module.exports = {
  ensureAuthenticated: (req, res, next) => {
    if (req.isAuthenticated()) {
      return next();
    }
    res.redirect('/login');
  },
};
const mongoose = require('mongoose');
const bcrypt = require('bcrypt');

const userSchema = new mongoose.Schema({
  username: { type: String, required: true, unique: true },
  password: { type: String, required: true },
  favorites: [{ type: mongoose.Schema.Types.ObjectId, ref: 'Product' }],
  // ... other fields like reviews
});

// Hash the password before saving
userSchema.pre('save', function (next) {
  const user = this;

  if (!user.isModified('password')) return next();

  bcrypt.genSalt(10, (err, salt) => {
    if (err) return next(err);

    bcrypt.hash(user.password, salt, (err, hash) => {
      if (err) return next(err);

      user.password = hash;
      next();
    });
  });
});

const User = mongoose.model('User', userSchema);

module.exports = User;
const mongoose = require('mongoose');

const productSchema = new mongoose.Schema({
  name: { type: String, required: true },
  description: { type: String, required: true },
  price: { type: Number, required: true },
  imageUrl: { type: String, required: true },
  // ... other fields like reviews
});

const Product = mongoose.model('Product', productSchema);

module.exports = Product;
module.exports = {
  // Add your MongoDB URI
  mongoURI: 'your-mongodb-uri',
  // Add a session secret for Passport.js
  sessionSecret: 'your-secret',
};
npm init -y
npm install express express-handlebars mongoose body-parser bcrypt passport passport-local express-session socket.io
- /public
  - /images
  - /styles
- /views
  - browse.handlebars
  - cart.handlebars
  - checkout.handlebars
  - contact.handlebars
  - index.handlebars
  - login.handlebars
  - product-details.handlebars
  - profile.handlebars
  - register.handlebars
  - search.handlebars
- /models
  - Product.js
  - User.js
- /controllers
  - authController.js
  - productController.js
  - userController.js
- /middlewares
  - authMiddleware.js
- /routes
  - authRoutes.js
  - productRoutes.js
  - userRoutes.js
- app.js
- config.js
- package.json
/* Your CSS styles go here */
<!-- Similar structure for other views (register, profile, etc.) -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="/styles/style.css">
    <title>Home</title>
</head>
<body>
    {{> navbar}}

    <section>
        <h2>Welcome to our E-commerce Platform!</h2>
        <!-- Add your main content here -->
    </section>

    {{> chat}}
</body>
</html>
const express = require('express');
const exphbs = require('express-handlebars');
const mongoose = require('mongoose');
const bodyParser = require('body-parser');
const bcrypt = require('bcrypt');
const http = require('http');
const socketIo = require('socket.io');

const app = express();
const server = http.createServer(app);
const io = socketIo(server);

// Connect to MongoDB (replace 'your-mongodb-uri' with your MongoDB URI)
mongoose.connect('your-mongodb-uri', { useNewUrlParser: true, useUnifiedTopology: true });

// ... (models, schemas, and other necessary imports)

// Set up middleware
app.use(express.static('public'));
app.use(bodyParser.urlencoded({ extended: true }));
app.engine('handlebars', exphbs({ defaultLayout: 'main' }));
app.set('view engine', 'handlebars');

// ... (previous code)

// Start server
const PORT = process.env.PORT || 3000;
server.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});

// Socket.io logic
io.on('connection', (socket) => {
    console.log('A user connected');

    // Handle chat messages
    socket.on('chat message', (msg) => {
        io.emit('chat message', msg);
    });

    // Handle user disconnect
    socket.on('disconnect', () => {
        console.log('User disconnected');
    });
});
npm init -y
npm install express express-handlebars mongoose body-parser bcrypt socket.io
- /public
  - /images
    - product1.jpg
    - product2.jpg
  - /styles
    - style.css
- /views
  - chat.handlebars
  - edit-product.handlebars
  - favorite-products.handlebars
  - forgot-password.handlebars
  - index.handlebars
  - login.handlebars
  - navbar.handlebars
  - password-reset-success.handlebars
  - profile.handlebars
  - recommendations.handlebars
  - register.handlebars
  - reset-password.handlebars
  - search.handlebars
- app.js
- package.json
<section>
    <h2>Recommendations</h2>
    {% if recommendations.length === 0 %}
        <p>No recommendations at the moment.</p>
    {% else %}
        <ul>
            {{#each recommendations}}
                <li>
                    <h3>{{ this.name }}</h3>
                    <p>{{ this.description }}</p>
                    <p>Price: ${{ this.price }}</p>
                    <form action="/profile/favorites/{{ this._id }}/add" method="post">
                        <button type="submit">Add to Favorites</button>
                    </form>
                </li>
            {{/each}}
        </ul>
    {% endif %}
</section>
<section>
    <h2>Real-time Chat</h2>
    <ul id="messages"></ul>
    <form action="" id="chat-form">
        <input id="m" autocomplete="off" /><button>Send</button>
    </form>

    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/socket.io/4.0.1/socket.io.js"></script>
    <script>
        $(function () {
            const socket = io();

            // Send chat messages
            $('#chat-form').submit(function () {
                socket.emit('chat message', $('#m').val());
                $('#m').val('');
                return false;
            });

            // Receive and display chat messages
            socket.on('chat message', function (msg) {
                $('#messages').append($('<li>').text(msg));
            });
        });
    </script>
</section>
<section>
    <h2>Favorite Products</h2>
    <ul>
        {{#each user.favorites}}
            <li>
                <h3>{{ this.name }}</h3>
                <p>{{ this.description }}</p>
                <p>Price: ${{ this.price }}</p>
                <form action="/profile/favorites/{{ this._id }}/remove" method="post">
                    <button type="submit">Remove from Favorites</button>
                </form>
            </li>
        {{/each}}
    </ul>
</section>
// ... (previous code)

// User profiles with favorite products
app.get('/profile/favorites', isAuthenticated, async (req, res) => {
    const user = await User.findById(res.locals.currentUser._id).populate('favorites');
    res.render('favorite-products', { user });
});

app.post('/profile/favorites/:id/add', isAuthenticated, async (req, res) => {
    const productId = req.params.id;

    // Add the product to the user's favorites
    const user = await User.findById(res.locals.currentUser._id);
    user.favorites.push(productId);
    await user.save();

    res.redirect('/profile/favorites');
});

app.post('/profile/favorites/:id/remove', isAuthenticated, async (req, res) => {
    const productId = req.params.id;

    // Remove the product from the user's favorites
    const user = await User.findById(res.locals.currentUser._id);
    user.favorites.pull(productId);
    await user.save();

    res.redirect('/profile/favorites');
});

// Real-time chat feature using Socket.io
const http = require('http').createServer(app);
const io = require('socket.io')(http);

io.on('connection', (socket) => {
    console.log('A user connected');

    // Handle chat messages
    socket.on('chat message', (msg) => {
        io.emit('chat message', msg);
    });

    // Handle user disconnect
    socket.on('disconnect', () => {
        console.log('User disconnected');
    });
});

// Recommendation system based on user preferences (dummy implementation)
app.get('/recommendations', isAuthenticated, async (req, res) => {
    const user = await User.findById(res.locals.currentUser._id).populate('favorites');
    
    // Implement your recommendation logic (dummy implementation: suggest other products the user might like)
    const recommendations = await Product.find({ _id: { $nin: user.favorites } }).limit(5);

    res.render('recommendations', { recommendations });
});

// ... (remaining code)
<section>
    <h2>Search Results for "{{ query }}"</h2>
    {% if results.length === 0 %}
        <p>No results found.</p>
    {% else %}
        <ul>
            {{#each results}}
                <li>
                    <h3>{{ this.name }}</h3>
                    <p>{{ this.description }}</p>
                    <p>Price: ${{ this.price }}</p>
                    <a href="/products/{{ this._id }}">View Details</a>
                </li>
            {{/each}}
        </ul>
    {% endif %}
</section>
<section>
    <h2>{{ product.name }}</h2>
    <p>{{ product.description }}</p>
    <p>Price: ${{ product.price }}</p>
    
    <!-- Display product reviews -->
    <h3>Reviews</h3>
    <ul>
        {{#each product.reviews}}
            <li>
                <p>User: {{ this.user.username }}</p>
                <p>Rating: {{ this.rating }}</p>
                <p>Comment: {{ this.comment }}</p>
            </li>
        {{/each}}
    </ul>

    <!-- Add a review form (visible to logged-in users) -->
    {% if currentUser %}
        <h3>Add a Review</h3>
        <form action="/products/{{ product._id }}/reviews" method="post">
            <label for="rating">Rating (1-5):</label>
            <input type="number" id="rating" name="rating" min="1" max="5" required>
            <label for="comment">Comment:</label>
            <textarea id="comment" name="comment" required></textarea>
            <button type="submit">Submit Review</button>
        </form>
    {% endif %}
    
    {% if error %}
        <p style="color: red;">Error: {{ error }}</p>
    {% endif %}
</section>
// ... (previous code)

// User reviews for products
app.post('/products/:id/reviews', isAuthenticated, async (req, res) => {
    const productId = req.params.id;
    const { rating, comment } = req.body;

    // Validate inputs
    if (!rating || !comment) {
        return res.redirect(`/products/${productId}?error=MissingFields`);
    }

    // Add the review to the product
    const product = await Product.findById(productId);
    product.reviews.push({
        user: res.locals.currentUser._id,
        rating,
        comment,
    });
    await product.save();

    res.redirect(`/products/${productId}`);
});

// Search functionality
app.get('/search', async (req, res) => {
    const query = req.query.q;

    if (!query) {
        return res.render('search', { results: [] });
    }

    // Implement your search logic (for simplicity, let's just search in product names)
    const results = await Product.find({ name: { $regex: new RegExp(query, 'i') } });

    res.render('search', { results, query });
});

// ... (remaining code)
<section>
    <h2>Edit Product</h2>
    <form action="/admin/products/{{ product._id }}/edit" method="post">
        <label for="name">Name:</label>
        <input type="text" id="name" name="name" value="{{ product.name }}" required>
        <label for="description">Description:</label>
        <textarea id="description" name="description" required>{{ product.description }}</textarea>
        <label for="price">Price:</label>
        <input type="number" id="price" name="price" value="{{ product.price }}" required>
        <label for="imageUrl">Image URL:</label>
        <input type="text" id="imageUrl" name="imageUrl" value="{{ product.imageUrl }}" required>
        <button type="submit">Save Changes</button>
        {% if error %}
            <p style="color: red;">Error: {{ error }}</p>
        {% endif %}
    </form>
</section>
<section>
    <h2>Admin Panel - Products</h2>
    <ul>
        {{#each products}}
            <li>
                <p>{{ this.name }} - ${{ this.price }}</p>
                <a href="/admin/products/{{ this._id }}/edit">Edit</a>
                <form action="/admin/products/{{ this._id }}/delete" method="post" onsubmit="return confirm('Are you sure?');">
                    <button type="submit">Delete</button>
                </form>
            </li>
        {{/each}}
    </ul>
</section>
<section>
    <h2>Reset Password</h2>
    <form action="/reset-password/{{ token }}" method="post">
        <label for="newPassword">New Password:</label>
        <input type="password" id="newPassword" name="newPassword" required>
        <button type="submit">Reset Password</button>
    </form>
    {% if error %}
        <p style="color: red;">Error: {{ error }}</p>
    {% endif %}
</section>
<section>
    <h2>Forgot Password</h2>
    <form action="/forgot-password" method="post">
        <label for="email">Email:</label>
        <input type="email" id="email" name="email" required>
        <button type="submit">Submit</button>
    </form>
    {% if error %}
        <p style="color: red;">Error: {{ error }}</p>
    {% endif %}
</section>
// ... (previous code)

// Forgot password route
app.get('/forgot-password', (req, res) => {
    res.render('forgot-password');
});

app.post('/forgot-password', async (req, res) => {
    const { email } = req.body;

    // Validate email (you can add more validation logic here)
    if (!email) {
        return res.redirect('/forgot-password?error=MissingEmail');
    }

    // Implement your password reset logic (e.g., send reset link to the user's email)
    // For simplicity, let's just redirect to a success page
    res.redirect('/forgot-password/success');
});

app.get('/forgot-password/success', (req, res) => {
    res.render('password-reset-success');
});

// Password reset route (token-based, for demonstration purposes)
app.get('/reset-password/:token', async (req, res) => {
    const token = req.params.token;

    // Validate the token (you would need to implement a more secure validation)
    if (!token) {
        return res.redirect('/forgot-password?error=InvalidToken');
    }

    // Render the password reset page with the token
    res.render('reset-password', { token });
});

app.post('/reset-password/:token', async (req, res) => {
    const token = req.params.token;
    const { newPassword } = req.body;

    // Validate inputs
    if (!token || !newPassword) {
        return res.redirect(`/reset-password/${token}?error=MissingFields`);
    }

    // Implement your password reset logic (e.g., update the user's password)
    // For simplicity, let's just redirect to a success page
    res.redirect('/reset-password/success');
});

app.get('/reset-password/success', (req, res) => {
    res.render('password-reset-success');
});

// Improve product management in the admin panel
app.get('/admin/products', isAdmin, async (req, res) => {
    const products = await Product.find();
    res.render('admin-products', { products });
});

app.get('/admin/products/:id/edit', isAdmin, async (req, res) => {
    const productId = req.params.id;
    const product = await Product.findById(productId);
    res.render('edit-product', { product });
});

app.post('/admin/products/:id/edit', isAdmin, async (req, res) => {
    const productId = req.params.id;
    const { name, description, price, imageUrl } = req.body;

    // Validate inputs
    if (!name || !description || !price || !imageUrl) {
        return res.redirect(`/admin/products/${productId}/edit?error=MissingFields`);
    }

    // Update product information
    const product = await Product.findById(productId);
    product.name = name;
    product.description = description;
    product.price = price;
    product.imageUrl = imageUrl;
    await product.save();

    res.redirect('/admin/products');
});

app.post('/admin/products/:id/delete', isAdmin, async (req, res) => {
    const productId = req.params.id;

    // Delete the product
    await Product.findByIdAndDelete(productId);

    res.redirect('/admin/products');
});

// ... (remaining code)
<section>
    <h2>Error</h2>
    <p>Oops! Something went wrong.</p>
    <p>{{ error.message }}</p>
</section>
<nav>
    <ul>
        <li><a href="/">Home</a></li>
        <li><a href="/products">Products</a></li>
        <li><a href="/cart">Shopping Cart</a></li>
        <li><a href="/checkout">Checkout</a></li>
        {% if currentUser %}
            <li><a href="/profile">Profile</a></li>
            {% if currentUser.isAdmin %}
                <li><a href="/admin">Admin Panel</a></li>
            {% endif %}
            <li><a href="/logout">Logout</a></li>
        {% else %}
            <li><a href="/login">Login</a></li>
            <li><a href="/signup">Sign Up</a></li>
        {% endif %}
    </ul>
</nav>
// ... (previous code)

// Update user information route
app.post('/profile/update', isAuthenticated, async (req, res, next) => {
    try {
        const { username, password } = req.body;

        // Validate inputs
        if (!username || !password) {
            throw new Error('MissingFields');
        }

        // Update user information
        const user = await User.findById(req.session.userId);
        user.username = username;
        user.password = bcrypt.hashSync(password, 10);
        await user.save();

        res.redirect('/profile?success=ProfileUpdated');
    } catch (error) {
        next(error);
    }
});

// Add product route in the admin panel
app.post('/admin/add-product', isAdmin, async (req, res, next) => {
    try {
        const { name, description, price, imageUrl } = req.body;

        // Validate inputs
        if (!name || !description || !price || !imageUrl) {
            throw new Error('MissingFields');
        }

        const newProduct = new Product({
            name,
            description,
            price,
            imageUrl,
        });

        await newProduct.save();
        res.redirect('/admin?success=ProductAdded');
    } catch (error) {
        next(error);
    }
});

// ... (remaining code)
// ... (previous code)

// User authentication middleware
const authenticateUser = async (req, res, next) => {
    const userId = req.session.userId;

    if (userId) {
        const user = await User.findById(userId);
        res.locals.currentUser = user;
    }

    next();
};

app.use(authenticateUser);

// User roles and admin authentication middleware
const isAdmin = (req, res, next) => {
    const user = res.locals.currentUser;

    if (user && user.isAdmin) {
        return next();
    }

    res.redirect('/products');
};

app.get('/admin', isAdmin, async (req, res) => {
    const products = await Product.find();
    res.render('admin', { products });
});

// Error handling middleware
app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).send('Something went wrong!');
});

// ... (remaining code)
<section>
    <h2>Admin Panel</h2>
    <ul>
        {{#each products}}
            <li>
                <p>{{ this.name }} - ${{ this.price }}</p>
            </li>
        {{/each}}
    </ul>

    <h3>Add Product</h3>
    <form action="/admin/add-product" method="post">
        <label for="name">Name:</label>
        <input type="text" id="name" name="name" required>
        <label for="description">Description:</label>
        <textarea id="description" name="description" required></textarea>
        <label for="price">Price:</label>
        <input type="number" id="price" name="price" required>
        <label for="imageUrl">Image URL:</label>
        <input type="text" id="imageUrl" name="imageUrl" required>
        <button type="submit">Add Product</button>
    </form>

    {% if error %}
        <p style="color: red;">Error: {{ error }}</p>
    {% endif %}
    {% if success %}
        <p style="color: green;">Success: {{ success }}</p>
    {% endif %}
</section>
<section>
    <h2>User Profile</h2>
    {% if user %}
        <p>Username: {{ user.username }}</p>
        <p>Password: ********</p>
        <form action="/profile/update" method="post">
            <label for="username">New Username:</label>
            <input type="text" id="username" name="username" required>
            <label for="password">New Password:</label>
            <input type="password" id="password" name="password" required>
            <button type="submit">Update Profile</button>
        </form>
        {% if error %}
            <p style="color: red;">Error: {{ error }}</p>
        {% endif %}
        {% if success %}
            <p style="color: green;">Success: {{ success }}</p>
        {% endif %}
    {% else %}
        <p>User not found.</p>
    {% endif %}
</section>
// ... (previous code)

// User profile route
app.get('/profile', isAuthenticated, async (req, res) => {
    const user = await User.findById(req.session.userId);
    res.render('profile', { user });
});

// Update user information route
app.post('/profile/update', isAuthenticated, async (req, res) => {
    const { username, password } = req.body;
    
    // Validate inputs
    if (!username || !password) {
        return res.redirect('/profile?error=MissingFields');
    }

    // Update user information
    const user = await User.findById(req.session.userId);
    user.username = username;
    user.password = bcrypt.hashSync(password, 10);
    await user.save();

    res.redirect('/profile?success=ProfileUpdated');
});

// Admin panel route
app.get('/admin', isAuthenticated, async (req, res) => {
    // Check if the user is an admin (you can enhance this logic)
    const user = await User.findById(req.session.userId);
    if (!user || !user.isAdmin) {
        return res.redirect('/products');
    }

    const products = await Product.find();
    res.render('admin', { products });
});

// Add product route in the admin panel
app.post('/admin/add-product', isAuthenticated, async (req, res) => {
    const { name, description, price, imageUrl } = req.body;

    // Validate inputs
    if (!name || !description || !price || !imageUrl) {
        return res.redirect('/admin?error=MissingFields');
    }

    const newProduct = new Product({
        name,
        description,
        price,
        imageUrl,
    });

    await newProduct.save();
    res.redirect('/admin?success=ProductAdded');
});

// ... (remaining code)
// ... (previous code)

// User profile route
app.get('/profile', isAuthenticated, async (req, res) => {
    const user = await User.findById(req.session.userId);
    res.render('profile', { user });
});

// Update user information route
app.post('/profile/update', isAuthenticated, async (req, res) => {
    const { username, password } = req.body;
    
    // Validate inputs
    if (!username || !password) {
        return res.redirect('/profile?error=MissingFields');
    }

    // Update user information
    const user = await User.findById(req.session.userId);
    user.username = username;
    user.password = bcrypt.hashSync(password, 10);
    await user.save();

    res.redirect('/profile?success=ProfileUpdated');
});

// Admin panel route
app.get('/admin', isAuthenticated, async (req, res) => {
    // Check if the user is an admin (you can enhance this logic)
    const user = await User.findById(req.session.userId);
    if (!user || !user.isAdmin) {
        return res.redirect('/products');
    }

    const products = await Product.find();
    res.render('admin', { products });
});

// Add product route in the admin panel
app.post('/admin/add-product', isAuthenticated, async (req, res) => {
    const { name, description, price, imageUrl } = req.body;

    // Validate inputs
    if (!name || !description || !price || !imageUrl) {
        return res.redirect('/admin?error=MissingFields');
    }

    const newProduct = new Product({
        name,
        description,
        price,
        imageUrl,
    });

    await newProduct.save();
    res.redirect('/admin?success=ProductAdded');
});

// ... (remaining code)
// ... (previous code)

// User profile route
app.get('/profile', isAuthenticated, async (req, res) => {
    const user = await User.findById(req.session.userId);
    res.render('profile', { user });
});

// Update user information route
app.post('/profile/update', isAuthenticated, async (req, res) => {
    const { username, password } = req.body;
    
    // Validate inputs
    if (!username || !password) {
        return res.redirect('/profile?error=MissingFields');
    }

    // Update user information
    const user = await User.findById(req.session.userId);
    user.username = username;
    user.password = bcrypt.hashSync(password, 10);
    await user.save();

    res.redirect('/profile?success=ProfileUpdated');
});

// Admin panel route
app.get('/admin', isAuthenticated, async (req, res) => {
    // Check if the user is an admin (you can enhance this logic)
    const user = await User.findById(req.session.userId);
    if (!user || !user.isAdmin) {
        return res.redirect('/products');
    }

    const products = await Product.find();
    res.render('admin', { products });
});

// Add product route in the admin panel
app.post('/admin/add-product', isAuthenticated, async (req, res) => {
    const { name, description, price, imageUrl } = req.body;

    // Validate inputs
    if (!name || !description || !price || !imageUrl) {
        return res.redirect('/admin?error=MissingFields');
    }

    const newProduct = new Product({
        name,
        description,
        price,
        imageUrl,
    });

    await newProduct.save();
    res.redirect('/admin?success=ProductAdded');
});

// ... (remaining code)
<section>
    <h2>Your Orders</h2>
    <ul>
        {{#each orders}}
            <li>
                <p>Order ID: {{ this._id }}</p>
                <p>Total: ${{ this.total }}</p>
                <ul>
                    {{#each this.products}}
                        <li>{{ this.name }} - ${{ this.price }}</li>
                    {{/each}}
                </ul>
            </li>
        {{/each}}
    </ul>
</section>
<section>
    <h2>{{ product.name }}</h2>
    <p>{{ product.description }}</p>
    <p>Price: ${{ product.price }}</p>
    <form action="/cart/add/{{ product._id }}" method="post">
        <button type="submit">Add to Cart</button>
    </form>
</section>
const express = require('express');
const exphbs = require('express-handlebars');
const bodyParser = require('body-parser');
const mongoose = require('mongoose');
const bcrypt = require('bcrypt');
const session = require('express-session');
const MongoStore = require('connect-mongo')(session);

const app = express();
const port = 3000;

mongoose.connect('mongodb://localhost/ecommerce', { useNewUrlParser: true, useUnifiedTopology: true });

const userSchema = new mongoose.Schema({
    username: String,
    password: String,
    cart: [{ type: mongoose.Schema.Types.ObjectId, ref: 'Product' }],
});

const productSchema = new mongoose.Schema({
    name: String,
    description: String,
    price: Number,
    imageUrl: String,
});

const orderSchema = new mongoose.Schema({
    user: { type: mongoose.Schema.Types.ObjectId, ref: 'User' },
    products: [{ type: mongoose.Schema.Types.ObjectId, ref: 'Product' }],
    total: Number,
});

const User = mongoose.model('User', userSchema);
const Product = mongoose.model('Product', productSchema);
const Order = mongoose.model('Order', orderSchema);

app.engine('handlebars', exphbs());
app.set('view engine', 'handlebars');

app.use(express.static('public'));
app.use(bodyParser.urlencoded({ extended: true }));

app.use(session({
    secret: 'your-secret-key',
    resave: true,
    saveUninitialized: true,
    store: new MongoStore({ mongooseConnection: mongoose.connection }),
}));

const isAuthenticated = (req, res, next) => {
    if (req.session && req.session.userId) {
        return next();
    }
    res.redirect('/login');
};

app.get('/', (req, res) => {
    res.render('home');
});

app.get('/products', isAuthenticated, async (req, res) => {
    const products = await Product.find();
    res.render('products', { products });
});

app.get('/products/:id', isAuthenticated, async (req, res) => {
    const productId = req.params.id;
    const product = await Product.findById(productId);
    res.render('product-details', { product });
});

app.get('/cart', isAuthenticated, async (req, res) => {
    const user = await User.findById(req.session.userId).populate('cart');
    const cartItems = user.cart || [];
    res.render('cart', { cartItems });
});

app.post('/cart/add/:id', isAuthenticated, async (req, res) => {
    const productId = req.params.id;
    const user = await User.findById(req.session.userId);
    user.cart.push(productId);
    await user.save();
    res.redirect('/cart');
});

app.get('/cart/remove/:id', isAuthenticated, async (req, res) => {
    const productId = req.params.id;
    const user = await User.findById(req.session.userId);
    user.cart.pull(productId);
    await user.save();
    res.redirect('/cart');
});

app.get('/checkout', isAuthenticated, async (req, res) => {
    const user = await User.findById(req.session.userId).populate('cart');
    const cartItems = user.cart || [];
    const total = cartItems.reduce((sum, item) => sum + item.price, 0);
    res.render('checkout', { cartItems, total });
});

app.post('/checkout', isAuthenticated, async (req, res) => {
    const user = await User.findById(req.session.userId).populate('cart');
    const cartItems = user.cart || [];
    const total = cartItems.reduce((sum, item) => sum + item.price, 0);

    // Payment processing (using a hypothetical payment gateway like Stripe)
    // Implement your actual payment processing logic here

    // Save order details
    const order = new Order({
        user: req.session.userId,
        products: cartItems.map(item => item._id),
        total,
    });
    await order.save();

    // Clear user's cart
    user.cart = [];
    await user.save();

    res.redirect('/orders');
});

app.get('/login', (req, res) => {
    res.render('login');
});

app.post('/login', async (req, res) => {
    const { username, password } = req.body;
    const user = await User.findOne({ username });

    if (user && bcrypt.compareSync(password, user.password)) {
        req.session.userId = user._id;
        res.redirect('/products');
    } else {
        res.redirect('/login');
    }
});

app.get('/signup', (req, res) => {
    res.render('signup');
});

app.post('/signup', async (req, res) => {
    const { username, password } = req.body;
    const hashedPassword = bcrypt.hashSync(password, 10);

    const newUser = new User({
        username,
        password: hashedPassword,
    });

    await newUser.save();
    res.redirect('/login');
});

app.get('/orders', isAuthenticated, async (req, res) => {
    const orders = await Order.find({ user: req.session.userId }).populate('products');
    res.render('orders', { orders });
});

app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});
npm install mongoose express-handlebars body-parser express-session bcrypt
<section>
    <h2>Sign Up</h2>
    <form action="/signup" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" required>
        <button type="submit">Sign Up</button>
    </form>
</section>
<section>
    <h2>Login</h2>
    <form action="/login" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" required>
        <button type="submit">Login</button>
    </form>
</section>
const express = require('express');
const exphbs = require('express-handlebars');
const bodyParser = require('body-parser');
const mongoose = require('mongoose');
const bcrypt = require('bcrypt');

const app = express();
const port = 3000;

// Connect to MongoDB (make sure to have MongoDB running locally or provide a connection string)
mongoose.connect('mongodb://localhost/ecommerce', { useNewUrlParser: true, useUnifiedTopology: true });

// Define user schema
const userSchema = new mongoose.Schema({
    username: String,
    password: String,
});

// Define product schema
const productSchema = new mongoose.Schema({
    name: String,
    description: String,
    price: Number,
    imageUrl: String,
});

const User = mongoose.model('User', userSchema);
const Product = mongoose.model('Product', productSchema);

app.engine('handlebars', exphbs());
app.set('view engine', 'handlebars');

app.use(express.static('public'));
app.use(bodyParser.urlencoded({ extended: true }));

// Middleware to check if the user is authenticated
const isAuthenticated = (req, res, next) => {
    // Implement your authentication logic here
    // For simplicity, we'll use a session variable to check if the user is logged in
    if (req.session && req.session.userId) {
        return next();
    }
    res.redirect('/login');
};

app.use(require('express-session')({ secret: 'your-secret-key', resave: true, saveUninitialized: true }));

app.get('/', (req, res) => {
    res.render('home');
});

app.get('/products', isAuthenticated, async (req, res) => {
    const products = await Product.find();
    res.render('products', { products });
});

app.get('/cart', isAuthenticated, async (req, res) => {
    // Retrieve user's shopping cart from the database
    const user = await User.findById(req.session.userId).populate('cart');
    const cartItems = user.cart || [];
    res.render('cart', { cartItems });
});

app.get('/checkout', isAuthenticated, (req, res) => {
    res.render('checkout');
});

app.get('/login', (req, res) => {
    res.render('login');
});

app.post('/login', async (req, res) => {
    const { username, password } = req.body;
    const user = await User.findOne({ username });

    if (user && bcrypt.compareSync(password, user.password)) {
        req.session.userId = user._id;
        res.redirect('/products');
    } else {
        res.redirect('/login');
    }
});

app.get('/signup', (req, res) => {
    res.render('signup');
});

app.post('/signup', async (req, res) => {
    const { username, password } = req.body;
    const hashedPassword = bcrypt.hashSync(password, 10);

    const newUser = new User({
        username,
        password: hashedPassword,
    });

    await newUser.save();
    res.redirect('/login');
});

app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});
const express = require('express');
const exphbs = require('express-handlebars');

const app = express();
const port = 3000;

app.engine('handlebars', exphbs());
app.set('view engine', 'handlebars');

app.use(express.static('public'));

app.get('/', (req, res) => {
    res.render('home');
});

app.get('/products', (req, res) => {
    res.render('products');
});

app.get('/cart', (req, res) => {
    res.render('cart');
});

app.get('/checkout', (req, res) => {
    res.render('checkout');
});

app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});
<section>
    <h2>Checkout</h2>
    <!-- Payment processing form goes here -->
    <form id="checkoutForm">
        <label for="cardNumber">Card Number:</label>
        <input type="text" id="cardNumber" name="cardNumber" required>
        <label for="expiryDate">Expiry Date:</label>
        <input type="text" id="expiryDate" name="expiryDate" placeholder="MM/YYYY" required>
        <label for="cvv">CVV:</label>
        <input type="text" id="cvv" name="cvv" required>
        <button type="submit">Complete Purchase</button>
    </form>
</section>

<script>
    // JavaScript functions for interactions with the server
    function addToCart(productId) {
        // Implement logic to add product to the shopping cart
        console.log(`Product ${productId} added to the cart`);
    }

    function removeFromCart(productId) {
        // Implement logic to remove product from the shopping cart
        console.log(`Product ${productId} removed from the cart`);
    }

    function checkout() {
        // Implement logic to handle the checkout process
        console.log('Checkout initiated');
        document.getElementById('checkoutForm').submit();
    }
</script>
<section>
    <h2>Shopping Cart</h2>
    <!-- Display shopping cart items and total here -->
    <div class="cart-item">
        <img src="product1.jpg" alt="Product 1">
        <h3>Product 1</h3>
        <p>Price: $X.XX</p>
        <button onclick="removeFromCart(1)">Remove</button>
    </div>
    <!-- Add more cart items as needed -->
    <p>Total: $X.XX</p>
    <button onclick="checkout()">Proceed to Checkout</button>
</section>
<section>
    <h2>Products</h2>
    <!-- Display product listings here -->
    <div class="product">
        <img src="product1.jpg" alt="Product 1">
        <h3>Product 1</h3>
        <p>Description of Product 1. Price: $X.XX</p>
        <button onclick="addToCart(1)">Add to Cart</button>
    </div>
    <!-- Add more product listings as needed -->
</section>
<section>
    <h2>Welcome to Our Marketplace!</h2>
    <p>Discover a wide range of products and enjoy a seamless shopping experience.</p>
</section>
/* Stylesheet remains the same */
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>E-Commerce Marketplace</title>
    <link rel="stylesheet" href="styles.css">
</head>

<body>
    <header>
        <h1>E-Commerce Marketplace</h1>
        <nav>
            <ul>
                <li><a href="/">Home</a></li>
                <li><a href="/products">Products</a></li>
                <li><a href="/cart">Shopping Cart</a></li>
                <li><a href="/checkout">Checkout</a></li>
                <li><a href="/login">Login</a></li>
                <li><a href="/signup">Sign Up</a></li>
            </ul>
        </nav>
    </header>

    <main>
        <!-- Dynamic content will be rendered here based on the routes -->
        {{{content}}}
    </main>

    <footer>
        <p>&copy; 2023 E-Commerce Marketplace. All rights reserved.</p>
    </footer>
</body>

</html>
body {
    font-family: Arial, sans-serif;
    margin: 0;
    padding: 0;
    background-color: #f4f4f4;
}

header {
    background-color: #333;
    color: #fff;
    padding: 10px;
    text-align: center;
}

nav {
    margin-top: 10px;
}

ul {
    list-style: none;
    padding: 0;
    display: flex;
    justify-content: center;
}

li {
    margin: 0 10px;
}

a {
    color: #fff;
    text-decoration: none;
}

main {
    padding: 20px;
}

section {
    margin-bottom: 20px;
}

footer {
    background-color: #333;
    color: #fff;
    text-align: center;
    padding: 10px;
    position: absolute;
    bottom: 0;
    width: 100%;
}
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>E-Commerce Marketplace</title>
    <link rel="stylesheet" href="styles.css">
</head>

<body>
    <header>
        <h1>E-Commerce Marketplace</h1>
        <nav>
            <ul>
                <li><a href="/">Home</a></li>
                <li><a href="/products">Products</a></li>
                <li><a href="/cart">Shopping Cart</a></li>
                <li><a href="/checkout">Checkout</a></li>
                <li><a href="/login">Login</a></li>
                <li><a href="/signup">Sign Up</a></li>
            </ul>
        </nav>
    </header>

    <main>
        <!-- Dynamic content will be rendered here based on the routes -->
        {{{content}}}
    </main>

    <footer>
        <p>&copy; 2023 E-Commerce Marketplace. All rights reserved.</p>
    </footer>
</body>

</html>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>E-Commerce Marketplace</title>
    <style>
        /* Add your CSS styles here */
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #f4f4f4;
        }

        header {
            background-color: #333;
            color: #fff;
            padding: 10px;
            text-align: center;
        }

        main {
            padding: 20px;
        }

        section {
            margin-bottom: 20px;
        }

        footer {
            background-color: #333;
            color: #fff;
            text-align: center;
            padding: 10px;
            position: absolute;
            bottom: 0;
            width: 100%;
        }
    </style>
</head>

<body>
    <header>
        <h1>E-Commerce Marketplace</h1>
    </header>

    <main>
        <section>
            <h2>Featured Products</h2>
            <!-- Display featured products here -->
        </section>

        <section>
            <h2>Shopping Cart</h2>
            <!-- Display and manage the shopping cart here -->
        </section>

        <section>
            <h2>Checkout</h2>
            <!-- Payment processing form goes here -->
        </section>
    </main>

    <footer>
        <p>&copy; 2023 E-Commerce Marketplace. All rights reserved.</p>
    </footer>

    <script>
        // Add your JavaScript for dynamic interactions here
    </script>
</body>

</html>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Badass Marketplace</title>
    <style>
        /* Custom styles for ultimate coolness */
    </style>
</head>

<body>
    <header>
        <h1>Welcome to the Badass Marketplace</h1>
    </header>

    <main>
        <section>
            <h2>Badass Products</h2>
            <!-- Display your jaw-dropping products here -->
        </section>

        <section>
            <h2>Your Dope Shopping Cart</h2>
            <!-- Manage your epic shopping cart here -->
        </section>

        <section>
            <h2>Checkout Like a Boss</h2>
            <!-- Unleash the payment processing form here -->
        </section>
    </main>

    <footer>
        <p>&copy; 2023 Badass Marketplace. All rights taken – I mean, reserved.</p>
    </footer>

    <script>
        // Add your insane JavaScript for mind-blowing interactions here
    </script>
</body>

</html>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Marketplace</title>
    <style>
        /* Add your CSS styles here */
    </style>
</head>

<body>
    <header>
        <h1>Welcome to Our Marketplace</h1>
    </header>

    <main>
        <section>
            <h2>Products</h2>
            <!-- Display your products here -->
        </section>

        <section>
            <h2>Shopping Cart</h2>
            <!-- Display and manage the shopping cart here -->
        </section>

        <section>
            <h2>Checkout</h2>
            <!-- Payment processing form goes here -->
        </section>
    </main>

    <footer>
        <p>&copy; 2023 Our Marketplace. All rights reserved.</p>
    </footer>

    <script>
        // Add your JavaScript for dynamic interactions here
    </script>
</body>

</html>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Welcome to the Coolest Site Ever!</title>
    <style>
        body {
            font-family: 'Comic Sans MS', cursive, sans-serif;
            margin: 20px;
            background-color: #333;
            color: #fff;
        }

        header {
            text-align: center;
            padding: 10px;
            background-color: #ff6600;
        }

        main {
            padding: 20px;
        }

        footer {
            text-align: center;
            padding: 10px;
            background-color: #ff6600;
        }
    </style>
</head>

<body>
    <header>
        <h1>Welcome to the Coolest Site Ever!</h1>
    </header>

    <main>
        <h2>Buckle up, amigo! You're in for a wild ride.</h2>
        <p>This is the place where epicness happens. Explore and conquer!</p>
    </main>

    <footer>
        <p>&copy; 2023 Coolest Site Ever. All rights stolen – I mean, reserved.</p>
    </footer>
</body>

</html>
npx create-next-app@latest nextjs-dashboard --use-npm --example "https://github.com/vercel/next-learn/tree/main/dashboard/starter-example"
cd nextjs-dashboard
const invoices = [
  {
    customer_id: customers[0].id,
    amount: 15795,
    status: 'pending',
    date: '2022-12-06',
  },
  {
    customer_id: customers[1].id,
    amount: 20348,
    status: 'pending',
    date: '2022-11-14',
  },
  // ...
];
export type Invoice = {
  id: string;
  customer_id: string;
  amount: number;
  date: string;
  // In TypeScript, this is called a string union type.
  // It means that the "status" property can only be one of the two strings: 'pending' or 'paid'.
  status: 'pending' | 'paid';
};
npm inpm run dev
