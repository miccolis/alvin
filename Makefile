.PHONY: verify clean vendor
verify:
	/Applications/Arduino.app/Contents/MacOS/Arduino --pref build.path=./build --verify --preserve-temp-files alvin.ino

upload:
	/Applications/Arduino.app/Contents/MacOS/Arduino --pref build.path=./build --upload --preserve-temp-files alvin.ino

clean:
	rm -rf ./build/*

vendor/LCD_Functions.h:
	curl https://raw.githubusercontent.com/sparkfun/GraphicLCD_Nokia_5110/master/Firmware/Nokia-5100-LCD-Example/LCD_Functions.h > ./vendor/LCD_Functions.h

vendor/LCD_Functions_license.txt:
	curl https://raw.githubusercontent.com/sparkfun/GraphicLCD_Nokia_5110/master/LICENSE.md > ./vendor/LCD_Functions_license.txt

vendor/rfid:
	curl -L -o ./vendor/rfid.zip https://github.com/miguelbalboa/rfid/archive/master.zip 
	unzip -d ./vendor ./vendor/rfid
	mv ./vendor/rfid-master ./vendor/rfid
	rm ./vendor/rfid.zip

vendor: vendor/LCD_Functions.h vendor/LCD_Functions_license.txt vendor/rfid
