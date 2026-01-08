import { useEffect, useState } from "react";
import api from "./services/api";
import Cart from "./components/Cart";
import EventLog from "./components/EventLog";

function App() {
  const [events, setEvents] = useState([]);

  const fetchEvents = async () => {
    const res = await api.get("/events");
    setEvents(res.data);
  };

  useEffect(() => {
    fetchEvents();
    const interval = setInterval(fetchEvents, 2000);
    return () => clearInterval(interval);
  }, []);

  return (
    <div>
      <h1>Smart Trolley Dashboard</h1>
      <Cart events={events} />
      <EventLog events={events} />
    </div>
  );
}

export default App;
