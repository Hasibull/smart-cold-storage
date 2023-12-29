package com.example.smartcoldstorage;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.cardview.widget.CardView;

import android.content.Intent;
import android.os.Bundle;
import android.text.Html;
import android.util.Log;
import android.view.View;
import android.widget.Switch;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {

    private TextView temperature, humidity, light, lpg, carbon;
    private CardView temperatureBtn, lightBtn;
    private Switch fan;
    DatabaseReference databaseReference;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        databaseReference = FirebaseDatabase.getInstance().getReference();

        temperature = findViewById(R.id.temperature);
        humidity = findViewById(R.id.humidity);
        light = findViewById(R.id.light);
        lpg = findViewById(R.id.lpg);
        carbon = findViewById(R.id.carbon);
        fan = findViewById(R.id.fan);
        ((TextView)findViewById(R.id.superscript)).setText(Html.fromHtml("<sup>2</sup>"));

        temperatureBtn = findViewById(R.id.temperature_btn);
        lightBtn = findViewById(R.id.light_btn);

        temperatureBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent i = new Intent(MainActivity.this, TemperatureTrend.class);
                startActivity(i);
            }
        });

        lightBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent i = new Intent(MainActivity.this, LightIntensityControlPanel.class);
                startActivity(i);
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();

        databaseReference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                for(DataSnapshot data : snapshot.getChildren()) {
                    LocalData rawData = data.getValue(LocalData.class);

                    temperature.setText(rawData.getTemperature());
                    humidity.setText(rawData.getHumidity());
                    carbon.setText(rawData.getCarbon());
                    light.setText(rawData.getLight());
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }
}