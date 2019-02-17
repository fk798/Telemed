import React, { Component } from 'react';
import { BrowserRouter, Route } from "react-router-dom"
import Login from "./components/Login"
import './App.css';

class App extends Component {
  render() {
    return (
      <div className="App">
        <BrowserRouter>
          <div>
            <h1>Telemed</h1>
            <h2>A quick and easy way to get biostat information.</h2>
            <Route path="/" component={Login}/>
          </div>
        </BrowserRouter>
      </div>
    );
  }
}

export default App;