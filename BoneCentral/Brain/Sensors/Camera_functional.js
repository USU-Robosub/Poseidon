import { Sensor, InternalState } from 'Sensor'

export default function Camera(sensorOptions){
  const internalState = InternalState({
    frequency: sensorOptions.frequency:
    defaultFrequency: 1
  })
  return Sensor(internalState, {
    connect: () => {

    },
    deactivate: () => {

    }
  });
}
