const { SerialPort } = require('serialport')


function sayHi()
{

// Встановлення параметрів порту
    const port = new SerialPort({
        path: '/dev/cu.wchusbserial140', // Шлях до порту
        baudRate: 9600, // Швидкість обміну даними повинна бути такою ж, як і на Arduino
    })

// Обробник події для отримання даних
    port.on('data', (data) => {
        // data - це буфер, що містить отримані дані від Arduino
        // Тут ви можете обробити ці дані, наприклад, перетворити їх у рядок:
        const response = data.toString('utf-8')
        console.log('Отримана відповідь від Arduino:', response)
    })

}
