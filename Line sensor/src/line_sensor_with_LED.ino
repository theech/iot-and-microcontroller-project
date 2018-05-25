/*
 * @author: Tee Hunter
 * @name of Project: Line sensor (Testing with black line and white floor) 
 * @duration: 14:26 - 05/25/2018
 * @lacation: Iot House
 */

// ປະກາດຂາໃຫ້ກັບ sensor ເປັນຂາຊ່ອງທີ 12 (define the pin of senser valiable called "sensor")
#define sensor 12

// ປະກາດຂາໃຫ້ກັບດອກໄຟ ເປັນຂາຊ່ອງທີ 2 
#define docphai 8            

// ປະກາດຕົວປ່ຽນຊື່ວ່າ data_sensor ເພື່ອເອົາໄວ້ເກັບຄ່າທີ່ໄດ້ມາຈາກ sensor (initialize valiable for reading data from line(input from sensor) called "data_sensor")
int data_sensor = 0;

// ຟັງຊັ້ນໃນການຕັ້ງຄ່າຕ່າງຂອງອຸປະກອນທີ່ເຮົາໃຊ້ ຕົວຢ່າງໃນນີ້ແມ່ນຕັ້ງຄ່າສຳຫລັບ sensor ກວດຈັບເສັ້ນຂຽວ-ດຳ        
void setup() {
  Serial.begin(9600);       // ຄວາມໄວ້ໃນການສົ່ງຄ່າຂອງ sensor (serial sequence that is showing on serial monitor)
  pinMode(sensor, INPUT);   // ຄຳສັ່ງເພື່ອໃຊ້ໃນການຮັບຄ່າຈາ sensor (input the value from line sensor)
  
  pinMode(docphai, HIGH);   // ຄຳສັ່ງເພື່ອໃຊ້ໃນການສົ່ງຄ່າຂອງດອກໄຟ
}

// ຟັງຊັນໃນການເຮັດວຽກແບບຊ້ຳໆ ມັນຈະເຊົາກໍຕໍ່ເມື່ອເຮົາອອກໂປຣແກຣມ
// This's going to be looping over and over again 
void loop() {
  data_sensor = digitalRead(sensor);    // ເອົາຄ່າທີ່ອ່ານມາຈາກ sensor ໄປກັບໄວ້ໃນຕົວປ່ຽນທີ່ຊື່ວ່າ "data_sensor" (store the value form "sensor" into "data_sensor")

    if (data_sensor == HIGH) 
        {
            digitalWrite(docphai, HIGH);
            Serial.print("Turn on the light: ");    // ສະແດງຄ່າ "Turn on the light" ຜ່ານທາງໜ້າຈໍ serial monitor
            Serial.print(data_sensor);              // ສະແດງຄ່າທີ່ໄດ້ຈາກ sensor ຜ່ານທາງໜ້າຈໍ ຖ້າເຫັນສີຂຽວຈະສະແດງຄ່າ 1, ແຕ່ຖ້າເຫັນເສັ້ນສີດຳຈະສະແດງຄ່າ 0 (ບໍ່ຕາຍໂຕມັນຂື້ນກັບລຸ້ນຂອງ sensor ບາງລຸ່ນອາດຈະເຫັນຄ່າສະຫຼັບກັບໂຕນີ້: ຂາວ: 0,ດຳ: 1)
        }
    else if (data_sensor == LOW)
        {
            digitalWrite(docphai, LOW);
            Serial.print("Turn on the light: ");    // ສະແດງຄ່າ "Turn off the light" ຜ່ານທາງໜ້າຈໍ serial monitor
            Serial.print(data_sensor);
        }
    else 
            Serial.print("Something wrong");

  Serial.print("\n");                   // ລົງແຖວເມື່ອວົງໄດ້ຮອບໜຶ່ງ
}