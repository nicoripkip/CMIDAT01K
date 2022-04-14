# CMIDAT01K

## Inhoudsopgave
<ul>
    <li><a href="#algemene-informatie">Algemene informatie</a></li>
    <li><a href="">Requirements</a></li>
    <li><a href="#installatie">Installatie</a></li>
    <li><a href="#branches">Branches</a></li>
    <li><a href="#autheur">Autheur</a></li>
</ul>

## Algemene informatie
<p>
Dit project is gemaakt om een sensor uit te lezen via The Things Network met behulp van het LoRa Protocol. Op dit project zijn een aantal sensoren
aangesloten. Deze sensoren zijn:

<ul>
    <li>BMP280 temperatuur sensor</li>
    <li>BMP280 druk sensor</li>
    <li>Vochtigheidssensor</li>
</ul>

Deze sensoren worden gebruikt om in mijn slaapkamer de leefomgeving te meten en de data te verzamelen. De data wordt verstuurd via <a href="https://en.wikipedia.org/wiki/LoRa">LoRa</a> en <a href="https://www.thethingsnetwork.org/">The Things Network</a>.

</p>


## Requirements
<ul>
    <li>PlatformIO op Visual Studio Code of Intellij</li>
    <li>Arduino framework</li>
    <li>BMP280 temperatuur sensor</li>
    <li>BMP280 druk sensor</li>
    <li>Vochtigheidssensor</li>
    <li>Heltec ESP32 LoRa V2</li>
    <li>Middleware zoals Thingsspeak/Azure of AWS</li>
    <li>Account op de The Things Network</li>
    <li>Random keukentafel ventilator op wisselspanning</li>
</ul>


## Installatie
<p>Voor uitgebreide installatie volg de <a href="https://github.com/nicoripkip/CMIDAT01K/wiki">wiki</a></p>


## Branches
<ul>
    <li><a href="https://github.com/nicoripkip/CMIDAT01K/tree/sender">Verzender</a></li>
    <li><a href="https://github.com/nicoripkip/CMIDAT01K/tree/receiver">Ontvanger</a></li>
    <li><a href="https://github.com/nicoripkip/CMIDAT01K/tree/gateway">Gateway</a></li>
</ul>


## Autheur
<p>
    <a href="https://github.com/nicoripkip">Nico van Ommen</a> | 1030808 | 1030808@hr.nl
</p>