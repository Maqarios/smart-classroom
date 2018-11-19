import React, { Component } from 'react';
import './App.css';

class App extends Component {
  state = {
    name: 'Admin',
    password: 'password',
    startTime: '13:30',
    hours: '',
    minutes: ''
  }


  handleInputChange = (event) => {
    const target = event.target;
    const value = target.type === 'checkbox' ? target.checked : target.value;
    console.log(value);
    const name = target.name;
    this.setState((prevState) => {
      return {
        ...prevState,
        [name]: value
      }
    });
  }

  submitExam = () => {

  }

  getHoursJSX = () => {
    const options = [];
    for (let i = 0; i < 6; i++) {
      if (i === 0) {
        options.push(<option value={i} key={`hours-${i}`} default>{i}</option>)
      } else {
        options.push(<option value={i} key={`hours-${i}`}>{i}</option>)
      }
    }
    return options;
  }

  getMinutesJSX = () => {
    const options = [];
    for (let i = 0; i < 60; i++) {
      if (i === 0) {
        options.push(<option value={i} key={`minutes-${i}`} default>{i}</option>)
      } else {
        options.push(<option value={i} key={`minutes-${i}`}>{i}</option>)
      }

    }
    return options;
  }

  render() {
    return (
      <div className="App background-pickachu">
        <div className="container-fluid" id="login">
          <div className="row">
            <div className="col-xs-10 col-sm-10 col-lg-6 align-center">
              <div className="form-wrap">
                <h1>Add start time of exam and duration, and don't forget to add your credentials ;)</h1>
                <form id="login-form">
                  <div className="form-group">
                    <label htmlFor="name" className="sr-only">Name</label>
                    <input type="name" name="name" id="name" className="form-control" value={this.state.name} onChange={this.handleInputChange} />
                  </div>
                  <div className="form-group">
                    <label htmlFor="password" className="sr-only">Password</label>
                    <input type="password" name="password" id="password" className="form-control" value={this.state.password} onChange={this.handleInputChange} />
                  </div>
                  <div className="form-group">
                    <label htmlFor="start-time" className="sr-only">Start Time</label>
                    <input type="time" name="startTime" id="start-time" className="form-control" value={this.state.startTime} onChange={this.handleInputChange} />
                  </div>
                  <div className="form-group">
                    <div className="row">
                      <div className="col-6">
                        <label htmlFor="hours" className="sr-only">Hours</label>
                        <select name="hours" id="hours" className="form-control" value={this.state.hours} onChange={this.handleInputChange}>
                          {this.getHoursJSX()}
                        </select>
                      </div>
                      <div className="col-6">
                        <label htmlFor="minutes" className="sr-only"></label>
                        <select name="minutes" id="minutes" className="form-control" value={this.state.minutes} onChange={this.handleInputChange}>

                          {this.getMinutesJSX()}
                        </select>
                      </div>
                    </div>
                  </div>
                  <input type="submit" id="btn-login" className="btn btn-custom btn-lg btn-block" value="Start Exam" onClick={this.submitExam} />
                </form>
                <hr />
              </div>
            </div>
          </div>
        </div>
        <footer id="footer" className="align-center">
          <div className="col-xs-12">
            <p className="h4">Powered by <strong>Pikachu</strong></p>
          </div>
        </footer>
      </div>
    );
  }
}

export default App;
