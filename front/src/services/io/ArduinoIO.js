export default class ArduinoIO {
  hasEndSymbol(data) {
    return data.includes('^');
  }

  handleData() {
    this.accumulatedData = this.accumulatedData.slice(0, this.accumulatedData.lastIndexOf('}') + 1)
    const dataObj = JSON.parse(this.accumulatedData)
    this.accumulatedData = ''

    this.updateGameData(dataObj);
  }

  updateGameData(dataObj) {
    this.app.updateGameData(dataObj)
  }

  processData(newData) {
    if (this.accumulatedData === undefined) {
      this.accumulatedData = '';
    }
    this.accumulatedData += newData;

    if (this.hasEndSymbol(this.accumulatedData)) {
      this.handleData();
    }
  }

  setApp(app) {
    this.app = app
  }

  setPort(port) {
    this.port = port
  }

  onSendData(action, args) {
    const data = {
      action: action,
    }

    Object.assign(data, args)
    const dataString = JSON.stringify(data)

    this.port.write(dataString)
  }
}
