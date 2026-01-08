const express = require("express");
const router = express.Router();
const CartEvent = require("../models/CartEvent");

router.post("/event", async (req, res) => {
  try {
    const event = await CartEvent.create(req.body);
    res.status(201).json(event);
  } catch (err) {
    res.status(500).json(err);
  }
});

router.get("/events", async (req, res) => {
  const events = await CartEvent.find().sort({ createdAt: -1 });
  res.json(events);
});

module.exports = router;
