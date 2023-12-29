package com.example.smartcoldstorage;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;

import com.androidplot.xy.CatmullRomInterpolator;
import com.androidplot.xy.LineAndPointFormatter;
import com.androidplot.xy.SimpleXYSeries;
import com.androidplot.xy.XYGraphWidget;
import com.androidplot.xy.XYPlot;
import com.androidplot.xy.XYSeries;
import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import com.github.mikephil.charting.interfaces.datasets.ILineDataSet;

import java.text.FieldPosition;
import java.text.Format;
import java.text.ParsePosition;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class TemperatureTrend extends AppCompatActivity {

    XYPlot temperatureChart;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_termperature_trend);

        temperatureChart = findViewById(R.id.temperature_trend);

        String[] timePeriod = {"1:34:16", "1:35:08", "1:36:36", "1:37:06", "1:38:47", "1:39:14", "1:40:16"};
        Number[] temperatures = {3.08, 3.04, 3.05, 3.04, 3.08, 3.03, 3.05};

        XYSeries temperatureSet = new SimpleXYSeries(Arrays.asList(temperatures),
                SimpleXYSeries.ArrayFormat.Y_VALS_ONLY, "Temperature");

        LineAndPointFormatter temperatureFormat = new LineAndPointFormatter(Color.BLUE, Color.RED, null, null);
        temperatureFormat.setInterpolationParams(new CatmullRomInterpolator.Params(7, CatmullRomInterpolator.Type.Centripetal));
        temperatureChart.addSeries(temperatureSet, temperatureFormat);
        temperatureChart.getGraph().getLineLabelStyle(XYGraphWidget.Edge.BOTTOM).setFormat(new Format() {
            @Override
            public StringBuffer format(Object o, StringBuffer stringBuffer, FieldPosition fieldPosition) {
                int i = Math.round(((Number)o).floatValue());
                return stringBuffer.append(timePeriod[i]);
            }

            @Override
            public Object parseObject(String s, ParsePosition parsePosition) {
                return null;
            }
        });
    }

//    private List<Entry> temperatureValues() {
//        ArrayList<Entry> temperatures = new ArrayList<>();
//        temperatures.add(new Entry(0, (float) 3.04));
//        temperatures.add(new Entry(1, (float) 3.06));
//        temperatures.add(new Entry(2, (float) 3.01));
//        temperatures.add(new Entry(3, (float) 3.10));
//        temperatures.add(new Entry(4, (float) 3.10));
//        temperatures.add(new Entry(4, (float) 3.09));
//        temperatures.add(new Entry(4, (float) 3.06));
//        temperatures.add(new Entry(4, (float) 3.07));
//        temperatures.add(new Entry(4, (float) 3.06));
//        temperatures.add(new Entry(4, (float) 3.07));
//
//        return temperatures;
//    }
}