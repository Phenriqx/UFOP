package view;

import model.Filtro;
import controller.SistemaController;

import java.awt.FlowLayout;
import javax.swing.*;
import java.time.*;
import java.util.Date;

public class FiltrosPanel extends JPanel {
    private JSpinner spinnerDataInicio;
    private JSpinner spinnerDataFim;
    private JSlider sliderTempMin;
    private JSlider sliderTempMax;
    private JTextField latitude;
    private JTextField longitude;
    private JSpinner spinnerRaio;
    private JButton limparFiltrosBtn;
    private JButton aplicarFiltrosBtn;
    private JCheckBox chkFiltroTempo;
    private JCheckBox chkFiltroTemperatura;
    private JCheckBox chkFiltroRaio;

    public FiltrosPanel() {
        inicializarComponentes();
    }

    private void inicializarComponentes() {
        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

        // Tempo
        JPanel pTempo = new JPanel(new FlowLayout(FlowLayout.LEFT));
        pTempo.setBorder(BorderFactory.createTitledBorder("Intervalo de Tempo"));

        chkFiltroTempo = new JCheckBox("Ativar");
        pTempo.add(chkFiltroTempo);
        SpinnerDateModel modelInicio = new SpinnerDateModel();
        spinnerDataInicio = new JSpinner(modelInicio);
        spinnerDataInicio.setEditor(new JSpinner.DateEditor(spinnerDataInicio, "yyyy-MM-dd HH:mm:ss"));

        SpinnerDateModel modelFim = new SpinnerDateModel();
        spinnerDataFim = new JSpinner(modelFim);
        spinnerDataFim.setEditor(new JSpinner.DateEditor(spinnerDataFim, "yyyy-MM-dd HH:mm:ss"));

        pTempo.add(new JLabel("Início: "));
        pTempo.add(spinnerDataInicio);
        pTempo.add(new JLabel("Fim: "));
        pTempo.add(spinnerDataFim);

        // Temperatura
        JPanel pTemp = new JPanel(new FlowLayout(FlowLayout.LEFT));
        pTemp.setBorder(BorderFactory.createTitledBorder("Intervalo de Temperatura: "));

        chkFiltroTemperatura = new JCheckBox("Ativar");
        pTemp.add(chkFiltroTemperatura);
        sliderTempMin = new JSlider(-50, 60, -50);
        sliderTempMax = new JSlider(-50, 60, 60);

        sliderTempMin.setMajorTickSpacing(10);
        sliderTempMin.setPaintTicks(true);
        sliderTempMax.setMajorTickSpacing(10);
        sliderTempMax.setPaintTicks(true);

        pTemp.add(new JLabel("Min: "));
        pTemp.add(sliderTempMin);
        pTemp.add(new JLabel("Max: "));
        pTemp.add(sliderTempMax);

        // Raio
        JPanel pRaio = new JPanel(new FlowLayout(FlowLayout.LEFT));
        pRaio.setBorder(BorderFactory.createTitledBorder("Raio a partir de coordenada: "));

        chkFiltroRaio = new JCheckBox("Ativar");
        pRaio.add(chkFiltroRaio);
        latitude = new JTextField(10);
        longitude = new JTextField(10);
        spinnerRaio = new JSpinner(new SpinnerNumberModel(0.0, 0.0, 1000.0, 10.0));

        pRaio.add(new JLabel("Latitude: "));
        pRaio.add(latitude);
        pRaio.add(new JLabel("Longitude: "));
        pRaio.add(longitude);
        pRaio.add(new JLabel("Raio: "));
        pRaio.add(spinnerRaio);

        aplicarFiltrosBtn = new JButton("Aplicar filtros");
        limparFiltrosBtn = new JButton("Limpar filtros");

        JPanel pBotoes = new JPanel(new FlowLayout(FlowLayout.LEFT));
        pBotoes.add(aplicarFiltrosBtn);
        pBotoes.add(limparFiltrosBtn);

        add(pTempo);
        add(pTemp);
        add(pRaio);
        add(pBotoes);
    }

    public void limparCampos() {
        chkFiltroTempo.setSelected(false);
        chkFiltroTemperatura.setSelected(false);
        chkFiltroRaio.setSelected(false);

        sliderTempMin.setValue(-50);
        sliderTempMax.setValue(60);

        latitude.setText("");
        longitude.setText("");

        spinnerRaio.setValue(0.0);
    }

    public double getTempMin() {
        return sliderTempMin.getValue();
    }
    
    public double getTempMax() {
        return sliderTempMax.getValue();
    }

    public JButton getLimparFiltrosBtn() {
        return limparFiltrosBtn;
    }

    public JButton getAplicarFiltrosBtn() {
        return aplicarFiltrosBtn;
    }

    public JSpinner getSpinnerDataInicio() {
        return spinnerDataInicio;
    }

    public JSpinner getSpinnerDataFim() {
        return spinnerDataFim;
    }

    public JSpinner getSpinnerRaio() {
        return spinnerRaio;
    }

    public JSlider getSliderTempMin() {
        return sliderTempMin;
    }
    
    public JSlider getSliderTempMax() {
        return sliderTempMax;
    }

    public JTextField getLongitudeTxt() {
        return longitude;
    }

    public JTextField getLatitudeTxt() {
        return latitude;
    }

    public LocalDateTime getDataInicio() {
        Date data = (Date) spinnerDataInicio.getValue();

        return data.toInstant()
                .atZone(ZoneId.systemDefault())
                .toLocalDateTime();
    }

    public LocalDateTime getDataFim() {
        Date data = (Date) spinnerDataFim.getValue();

        return data.toInstant()
                .atZone(ZoneId.systemDefault())
                .toLocalDateTime();
    }

    public Double getLatitudeCentro() {
        String txt = latitude.getText().trim();
        return txt.isEmpty() ? null : Double.parseDouble(txt.replace(',', '.'));
    }

    public Double getLongitudeCentro() {
        String txt = longitude.getText().trim();
        return txt.isEmpty() ? null : Double.parseDouble(txt.replace(',', '.'));
    }

    public Double getRaioKm() {
        return (Double) spinnerRaio.getValue();
    }

    public boolean isFiltroTempoAtivo() {
        return chkFiltroTempo.isSelected();
    }

    public boolean isFiltroTemperaturaAtivo() {
        return chkFiltroTemperatura.isSelected();
    }

    public boolean isFiltroRaioAtivo() {
        return chkFiltroRaio.isSelected();
    }
}