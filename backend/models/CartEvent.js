const mongoose = require("mongoose");

const cartEventSchema = new mongoose.Schema({
  product: String,
  price: Number,
  event: String,
  total: Number,
  createdAt: { type: Date, default: Date.now }
});

module.exports = mongoose.model("CartEvent", cartEventSchema);
