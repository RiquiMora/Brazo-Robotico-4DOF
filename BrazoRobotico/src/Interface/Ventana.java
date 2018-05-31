package Interface;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import javax.swing.*;
import java.awt.event.*; 
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import static java.awt.image.ImageObserver.ERROR;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Enumeration;


public class Ventana extends JFrame{
    
    private OutputStream Output = null;
    private InputStream Input = null;
    SerialPort serialPort;
    private final String PORT_NAME = "COM7";
    private static final int TIME_OUT = 2000;
    private static final int DATA_RATE = 9600;
    private boolean flag_modo = false;
    private final JTextArea txtA_comandos = new JTextArea();
    //private final JScroolPane  scroll= 
    JScrollPane scroll= new JScrollPane(txtA_comandos);
    private JButton btn_comando[] = new JButton[2];
    private final JPanel panel_controlBotones = new JPanel();
    private final JLabel etiquete;
    private Analizador analizar =  new Analizador();
    
    public Ventana()
    {
        etiquete = new JLabel("");
        btn_comando[0] = new JButton("Programar");
        btn_comando[1] = new JButton("Cambiar Funcion");
        
        this.setVisible(true);
        this.setLayout(null);
        this.setSize(500, 420);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        
        this.add(scroll);
        this.add(panel_controlBotones);
        this.add(etiquete);
        
        panel_controlBotones.setBounds(50,20, 400, 250);
        scroll.setBounds(50 ,20 , 400, 250);
        
        
        this.add(btn_comando[0]);
        btn_comando[0].setBounds(90, 310, 130, 50);
          
        
        Eventos();
        iniciaConexion();
    }
    
    private int RecibirDatos() throws IOException {
        int Output = 0;
        Output = Input.read();
        return Output;
    }

    public synchronized void serialEvent(SerialPortEvent oEvent) {
    if (oEvent.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
    try {
    int datos;
    datos = RecibirDatos(); //Se invoca la función RecibirDatos()

    //Esta función devolverá un valor entero en formato ASCII.
    System.out.println((char)datos); //Se imprime en el mensaje

    //haciendo la conversión de ASCII a nuestro alfabeto.
    } catch (Exception e) {
    System.err.println(e.toString());
    }
    }
    }
    private void iniciaConexion()
    {
        
        CommPortIdentifier portId = null;
        Enumeration portEnum = CommPortIdentifier.getPortIdentifiers();

        while (portEnum.hasMoreElements()) 
        {
            CommPortIdentifier currPortId = (CommPortIdentifier) portEnum.nextElement();
            if (PORT_NAME.equals(currPortId.getName())) 
            {
                portId = currPortId;
                break;
            }
        }

        if (portId == null) 
        {
            showError(PORT_NAME);
            System.exit(ERROR);
            return;
        }

        try 
        {
            serialPort = (SerialPort) portId.open(this.getClass().getName(), TIME_OUT);
            serialPort.setSerialPortParams(DATA_RATE,
                    SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE);
            Output = serialPort.getOutputStream();

        } catch (Exception e) {
            System.exit(ERROR);
        }
    }
    private void showError(String errorMessage){
            JOptionPane.showMessageDialog(null,errorMessage,"Error",JOptionPane.ERROR_MESSAGE);
    }
    public void Eventos()
    {
        btn_comando[0].addActionListener(new EscuchaProgramar());
    }
    
    class EscucharEtiqueta implements KeyListener
    {

        @Override
        public void keyTyped(KeyEvent e) {
            if(flag_modo){}
        }

        @Override
        public void keyPressed(KeyEvent e) {
            throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        }

        @Override
        public void keyReleased(KeyEvent e) {
            throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        }
        
    }
    
    class EscuchaProgramar implements ActionListener
    {

        @Override
        public void actionPerformed(ActionEvent e) {
            String data = txtA_comandos.getText();
            String pasos[] = data.split("\n");
            String aux = "";

            for (int i = 0; i < pasos.length; i++) 
            {
             aux = aux + pasos[i];
            }  
            
            if(analizar.esValido(aux)){
                try 
                {
                    Output.write(aux.getBytes());
                } 
                catch (IOException ex) 
                {
                    System.exit(ERROR);
                }
            }else{
                System.out.println("que mamadas");
            }
            
        }
    
    }
}
