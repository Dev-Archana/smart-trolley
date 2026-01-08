export default function EventLog({ events }) {
  return (
    <div>
      <h3>Event Log</h3>
      {events.map((e, i) => (
        <div key={i}>
          {e.event} | {e.product} | ₹{e.price}
        </div>
      ))}
    </div>
  );
}
