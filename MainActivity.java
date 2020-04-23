package com.example.iot_minggu8;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


public class MainActivity extends AppCompatActivity {

    TextView statusLdr;
    TextView statusFlame;
    TextView statusLed;
    TextView statusBuzzer;

    String valueLdr;
    String valueFlame;
    String valueLed;
    String valueBuzzer;

    DatabaseReference dref;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        statusFlame = (TextView) findViewById(R.id.txtView_valueFlameSensor);
        statusLdr = (TextView) findViewById(R.id.txtView_valueLdr);
        statusBuzzer = (TextView) findViewById(R.id.txtView_valueBuzzer);
        statusLed = (TextView) findViewById(R.id.txtView_valueLed);

        dref = FirebaseDatabase.getInstance().getReference();
        dref.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                valueFlame = dataSnapshot.child("Node1/flame").getValue().toString();
                if(valueFlame.equals("1")){
                    statusFlame.setText("Tidak ada api");
                }
                else{
                    statusFlame.setText("Api terdeteksi");
                }

                //set status BEZZER
                valueBuzzer = dataSnapshot.child("Node1/buzzer").getValue().toString();
                if(valueBuzzer.equals("1")){
                    statusBuzzer.setText("ON");
                }
                else{
                    statusBuzzer.setText("OFF");
                }

                //set status LDR
                valueLdr = dataSnapshot.child("Node1/ldr").getValue().toString();
                if(valueLdr.equals("1")){
                    statusLdr.setText("Kurang cahaya");
                }
                else{
                    statusLdr.setText("Cukup Cahaya");
                }

                //set status LED
                valueLed = dataSnapshot.child("Node1/led").getValue().toString();
                if(valueLed.equals("1")){
                    statusLed.setText("ON");
                }
                else{
                    statusLed.setText("OFF");
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });
    }
}
