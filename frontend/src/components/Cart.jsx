export default function Cart({ events }) {
  const total = events.length ? events[0].total : 0;

  return (
    <div>
      <h2>Total Amount: ₹{total}</h2>
    </div>
  );
}
