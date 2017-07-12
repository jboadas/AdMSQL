function verificarTexto(consOut){
    var match = /no existe/.test(consOut);
    if(match==false){
        match = /STOPPED/.test(consOut);
        if(match==false){
            match = /START_PENDING/.test(consOut);
            if(match==false){
                match = /RUNNING/.test(consOut);
                if(match==false){
                    match = /STOP_PENDING/.test(consOut);
                    if(match==false){
                        match = /successfully installed/.test(consOut);
                        if(match==false){
                            match = /DeleteService/.test(consOut);
                            if(match==false){
                                match = /Denied/.test(consOut);
                                if(match==false){
                                    return "DESCONOCIDO";
                                }else{
                                    return "NEGADO";
                                }

                            }else{
                                return "BORRADO";
                            }

                        }else{
                            return "INSTALADO";
                        }

                    }else{
                        return "DETENIENDOSE";
                    }

                }else{
                    return "INICIADO";
                }
            }else{
                return "INICIANDO";
            }

        }else{
            return "DETENIDO";
        }

    }else{
        return "NOEXISTE";
    }
}

