# 🚀 Controle de Servomotor por PWM

## 📌 Descrição

Esta tarefa envolve o uso do módulo PWM do microcontrolador RP2040 para simular o controle de um servomotor utilizando a ferramenta Pico SDK. A atividade será realizada em um ambiente de simulação com o Wokwi e utilizando a Ferramenta Educacional BitDogLab para análise do LED RGB.

## 📌 Funcionamento

### ⚙️ Configuração da GPIO 22 para PWM

Definir a frequência de PWM para aproximadamente 50Hz (período de 20ms).

### 🎯 Posição de 180 graus

Definir o ciclo ativo do PWM para 2.400µs (Duty Cycle de 0,12%).

Manter essa posição por 5 segundos.

### 🎯 Posição de 90 graus

Definir o ciclo ativo do PWM para 1.470µs (Duty Cycle de 0,0735%).

Manter essa posição por 5 segundos.

### 🎯 Posição de 0 graus

Definir o ciclo ativo do PWM para 500µs (Duty Cycle de 0,025%).

Manter essa posição por 5 segundos.

### 💡 Teste com LED RGB

Observar o comportamento da iluminação do LED RGB na GPIO 12.

### 🎥 Vídeo com o funcionamento
https://drive.google.com/file/d/1jOYAAgbEatJbPh0dKNnd0nwTpejiNp4q/view?usp=sharing

### 🎯 Conclusão

Esta tarefa permite explorar o uso do PWM no Raspberry Pi Pico para controle de servomotores, além de integrar conceitos de programação embarcada e simulação de circuitos eletrônicos.

