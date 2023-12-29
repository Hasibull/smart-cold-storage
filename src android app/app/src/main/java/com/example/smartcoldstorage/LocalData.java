package com.example.smartcoldstorage;

public class LocalData {
    private String temperature, humidity, carbon, lpg, light, fan;

    public LocalData() {

    }

    public LocalData(String temperature, String humidity, String light, String lpg, String carbon, String fan) {
        this.temperature = temperature;
        this.humidity = humidity;
        this.light = light;
        this.lpg = lpg;
        this.carbon = carbon;
        this.fan = fan;
    }

    public void setTemperature(String temperature) {
        this.temperature = temperature;
    }

    public void setHumidity(String humidity) {
        this.humidity = humidity;
    }

    public void setLight(String light) {
        this.light = light;
    }

    public void setLpg(String lpg) {
        this.lpg = lpg;
    }

    public void setCarbon(String carbon) {
        this.carbon = carbon;
    }

    public void setFan(String fan) {
        this.fan = fan;
    }

    public String getTemperature() {
        return temperature;
    }

    public String getHumidity() {
        return humidity;
    }

    public String getLight() {
        return light;
    }

    public String getLpg() {
        return lpg;
    }

    public String getCarbon() {
        return carbon;
    }

    public String getFan() {
        return fan;
    }
}
