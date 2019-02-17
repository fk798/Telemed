import React, { Component } from "react";
//import { Button } from "react-materialize";

class Login extends Component {
    constructor (props) {
        super(props);
        this.state = {
            userName: '',
            data: []
        }
        this.handleUserNameChange = this.handleUserNameChange.bind(this);
        this.handleSubmit = this.handleSubmit.bind(this);
    }
    
    handleUserNameChange (event) {
      this.setState({
          userName: event.target.value
      })
    }
    handleSubmit = async event => {
        let u = this.state.userName
        this.setState({
            userName: ""
        })
        event.preventDefault();
        fetch('http://localhost:5000/users/' + u).then(response => response.json()).then(data => (this.setState({data})))
    }
    
    render() {
        return (
            <div className="row">
            <form className="col s12" onSubmit={this.handleSubmit}>
              <div className="row">
                <div className="input-field col s6">
                    <label htmlFor="user_name" >User Name:</label> <br></br>
                    <input id="user_name" type="text" className="validate" value={this.state.userName} onChange={this.handleUserNameChange}/>
                </div>
              </div>
              <button>Submit</button>
            </form>
          </div>
        )
    }
}
export default Login;