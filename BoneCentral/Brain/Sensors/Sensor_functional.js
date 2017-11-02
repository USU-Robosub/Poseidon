export const States = {
  Idle: 0,
  Activating: 1,
  Activated: 2
}

export function Sensor(internalState, options){
  const sensor = {
    get activated() {
      return internalState.state == States.Activated
    },
    get hasReading() {
      return internalState.latestReading.timestamp != null
    },
    get timestamp() {
      return internalState.latestReading.timestamp
    },
    onreading: null,
    onactivate: null,
    onerror: null
  }
  sensor.stop = () => {
    if(internalState.state == States.Idle)
      return
    internalState.state = States.Idle
    options.deactivate();
  }
  sensor.start = () => {
    if(internalState.state == States.Activating ||
      internalState.state == States.Activated)
      return

    internalState.state = States.Activating
    const connected = options.connect()
    if(!connected){
      sensor.onerror("Error Connecting") // <- change event
      return
    }
  }
  return sensor
}

export function InternalState(options){
  return {
    state: states.Idle,
    frequency: options.frequency || options.defaultFrequency,
    lastEventFiredAt: null,
    pendingReadingNotification: false,
    latestReading: {
      timestamp: null,
      reading: null
    }
  }
}
