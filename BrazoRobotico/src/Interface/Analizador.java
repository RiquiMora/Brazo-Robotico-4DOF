package Interface;

public class Analizador {
    
    boolean parentesis_derecho = false;
    boolean parentesis_izquierdo = false;
    boolean punto_coma = false;
    
    public Analizador(){
    }
    
    public boolean esValido(String codigo)
    {
        String aux = "";
        for (int i = 0; i < codigo.length(); i++) {
           char c = codigo.charAt(i);

           if(c == '(') {
              parentesis_derecho=true;
              if(esTokenValido(aux))
              {
                  aux = "";
              }else
              {
                  return false;
              }
           }
           else if(c == ')') 
           {
               parentesis_izquierdo=true; 
               if(esNumerico(aux))
               {
                   aux = "";
               }else
               {
                   return false;
               }
           }
           else if(c == ';') punto_coma = true;
           else aux = aux + c;
        }
        
        if( punto_coma == false || parentesis_derecho == false || 
            parentesis_izquierdo == false) return false;
        
        
        return true;
    }
    
    private boolean esTokenValido(String token)
    {
        boolean valido = true;
        switch(token)
        {
            case "base": valido = true; break;
            case "hombro": valido = true; break;
            case "garra": valido = true; break;
            case "brazo": valido = true; break;
            default: valido = false; break;
        }
        return valido;
    }
    
    private boolean esNumerico(String numero)
    {
        for (int i = 0; i < numero.length(); i++) {
            char c =  numero.charAt(i);
            if(c == '0') continue;
            else if(c == '1') continue;
            else if(c == '2') continue;
            else if(c == '3') continue;
            else if(c == '4') continue;
            else if(c == '5') continue;
            else if(c == '6') continue;
            else if(c == '7') continue;
            else if(c == '8') continue;
            else if(c == '9') continue;
            else return false;
        }
        
        return true;
    }
    
    
}
