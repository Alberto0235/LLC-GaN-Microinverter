# ⚡ GaN-Based LLC Resonant Converter for Photovoltaic Micro-Inverter

**Type:** Bachelor's Internship Project  
**University:** Alma Mater Studiorum — University of Bologna, Cesena Campus  
**Degree:** B.Sc. in Electronic Engineering  
**Academic Supervisor:** Prof. Andrea Natale Tallarico  
**Academic Year:** 2024/2025

---

## 🎯 Project Summary

Design and simulation of a **GaN-based full-bridge LLC resonant step-up converter** as the first power stage of a 400W photovoltaic micro-inverter. The system boosts the PV panel output (~24V DC) to a 400V DC bus, which feeds a downstream H-bridge inverter producing a clean 230V_RMS / 50Hz sinusoidal output.

**Key result: 97.88% LLC efficiency and 94.71% end-to-end system efficiency at 100 kHz.**

---

## 📐 Design Specifications

| Parameter | Value |
| :--- | :--- |
| Input Voltage | 20–40 V (24 V nominal) |
| Output Voltage | 400 V DC |
| Output Power | 400 W |
| Switching Frequency | 100 kHz – 1 MHz |
| Topology | Full-Bridge LLC Resonant Converter |
| Switching Devices | GaN MOSFETs (EPC series, GaN Systems) |

---

## 🔑 Why LLC + GaN?

The LLC resonant converter was selected after a comparative analysis of isolated high step-up DC-DC topologies. It achieves **Zero Voltage Switching (ZVS)** throughout the operating range, dramatically reducing switching losses — a critical advantage at the high frequencies enabled by GaN technology.

| Topology | Efficiency |
| :--- | :---: |
| High Step-Up Forward | 86.9% |
| High Step-Up Push-Pull | 92.7% |
| High Step-Up Isolated SEPIC | 93.8% |
| High Step-Up Dual Flyback | 95.3% |
| **High Step-Up LLC** | **97.5%** |

GaN MOSFETs were chosen over Silicon for their low R_DS(on), high switching speed, and compact die area — enabling efficient operation from 100 kHz to 1 MHz with significantly reduced conduction and switching losses compared to conventional Si devices.

---

## 🛠️ Design Flow

The sizing methodology follows the Infineon Application Note *"Resonant LLC Converter: Operation and Design"* and consists of:

1. **Select Q and m** from resonant tank gain plot analysis
2. **Verify K_max** satisfies the required voltage gain across the full input range (20–40V)
3. **Compute resonant component values** (L_r, C_r, L_m, N_p/N_s)
4. **Optimize dead time** to ensure ZVS turn-on of primary-side GaN MOSFETs across the full load range, preventing shoot-through while minimizing body diode conduction losses
5. **Validate in LTspice** with real GaN MOSFET SPICE models (EPC GaN Library)

The resonant tank voltage gain:

$$K(Q, m, F_x) = \frac{F_x^2(m-1)}{\sqrt{\left(mF_x^2-1\right)^2 + F_x^2\left(F_x^2-1\right)^2(m-1)^2Q^2}}$$

where $F_x = f_s/f_r$ is the normalized switching frequency, $Q$ is the quality factor, and $m = (L_r + L_m)/L_r$ is the inductance ratio.

### Optimal Component Values (m = 6.3)

| f_sw | Q | N_p/N_s | f_s,min | L_r | C_r | L_m |
| :--- | :---: | :---: | :--- | :--- | :--- | :--- |
| 100 kHz | 0.4 | 0.06 | 48.9 kHz | 743 nH | 3.4 µF | 3.93 µH |
| 500 kHz | 0.3 | 0.06 | 218.5 kHz | 111.46 nH | 909 nF | 590.7 nH |
| 1 MHz | 0.2 | 0.06 | 417 kHz | 37.15 nH | 681.77 nF | 196.91 nH |

---

## 📊 Simulation Results

### LLC Converter Efficiency

| f_sw | P_in | P_out | Efficiency |
| :--- | :---: | :---: | :---: |
| 100 kHz | 408.91 W | 400.25 W | **97.88%** |
| 500 kHz | 419.34 W | 400.57 W | 95.52% |
| 1 MHz | 427.03 W | 400.31 W | 93.74% |

### Complete Micro-Inverter System Efficiency

| f_sw | LLC Eff. | Inverter Eff. | System Eff. |
| :--- | :---: | :---: | :---: |
| 100 kHz | 97.88% | 98.79% | **94.71%** |
| 500 kHz | 95.52% | 97.65% | 92.64% |
| 1 MHz | 93.74% | 95.76% | 88.70% |

The efficiency–frequency trade-off is clear: higher switching frequency reduces passive component size and cost but increases losses due to transformer core losses (hysteresis and eddy currents), capacitor dielectric losses, and the increasing fraction of each period spent in switching transitions.

### Efficiency vs. Output Power (100W – 400W)

Simulations were run across the full load range at all three switching frequencies to characterize the efficiency profile. Peak efficiency shifts to higher power levels as switching frequency increases, reflecting the interplay between conduction losses (dominant at heavy load) and switching losses (dominant at light load).

![Efficiency vs Power](images/eff_vs_power.png)

---

## 🖥️ LTspice Simulations

All simulations use real **GaN MOSFET SPICE models** from two device families — **EPC** and **GaN Systems (Infineon Technologies Company)** — for accurate loss estimation, including parasitic capacitances and non-ideal switching behavior. Multiple device variants from both families were evaluated during the design phase to select the optimal transistor for each stage (see `device_comparison/`).

The secondary-side bridge uses GaN MOSFETs as a **synchronous rectifier** instead of diodes, eliminating forward-voltage drop losses and improving overall efficiency through their low R_DS(on).

### LLC Converter (standalone)
![LLC Circuit](images/llc_circuit.png)

### Complete Micro-Inverter (LLC + H-Bridge + LC Filter)
![Full Circuit](images/full_circuit.png)

### Output Waveform — 230V_RMS / 50Hz
![Sinusoidal Output](images/sinewave_output.png)

---

## 🔧 Tools & Code

### Sizing Tool — `c/llc_sizing.c`

A C program that automates the full LLC component sizing workflow. Given design specs (V_in, V_out, P_out, f_r, Q, m, F_x,min, K_max), it computes L_r, C_r, L_m, N_p/N_s, and f_s,min — eliminating manual calculation errors during design iteration.

```bash
gcc llc_sizing.c -o llc_sizing -lm
./llc_sizing
```

### Gain Plot — `matlab/llc_gain_plot.m`

MATLAB script that plots the resonant tank voltage gain K(Q, m, F_x) for multiple Q values and three values of m. Used to graphically extract K_max and F_x,min as inputs to the sizing tool.

```matlab
% Run in MATLAB — generates gain plots for m = [3, 6, 15]
run('llc_gain_plot.m')
```

---

## 📂 Repository Structure

```
llc-gan-microinverter/
│
├── README.md
├── report/
│   └── LLC_Converter_Report.pdf          # Full internship report (EN)
│
├── ltspice/
│   ├── llc_converter/                    # LLC stage standalone (3 frequencies)
│   │   ├── Circuit_400W_100KHz.asc
│   │   ├── Circuit_400W_500KHz.asc
│   │   ├── Circuit_400W_1MHz.asc
│   │   ├── dead_time_analysis/           # Dead time optimization study
│   │   │   ├── Dead_time.asc
│   │   │   ├── Dead_time_V1.asc
│   │   │   └── Dead_time_V2.asc
│   │   └── EPC_GaN_Library.lib
│   │
│   ├── full_microinverter/               # Complete LLC + H-bridge + LC filter
│   │   ├── Full_100KHz.asc
│   │   ├── Full_500KHz.asc
│   │   └── Full_1MHz.asc
│   │
│   ├── efficiency_sweep/                 # Full system sweep 100W–400W
│   │   ├── Full_100W_100KHz.asc
│   │   ├── Full_100W_500KHz.asc
│   │   ├── Full_150W_100KHz.asc
│   │   └── ...
│   │
│   └── device_comparison/               # GaN device selection study
│       ├── Components/                  # SPICE models for evaluated devices
│       └── ...
│
├── matlab/
│   └── llc_gain_plot.m
│
├── c/
│   └── llc_sizing.c
│
└── images/
    ├── llc_circuit.png
    ├── full_circuit.png
    ├── sinewave_output.png
    └── eff_vs_power.png
```

---

## 🛠️ Tools Used

| Tool | Purpose |
| :--- | :--- |
| **LTspice** | Circuit simulation and efficiency analysis |
| **MATLAB** | Resonant tank gain plotting and design verification |
| **C (gcc)** | Automated component sizing tool |
| **LaTeX** | Technical report preparation |
| **GaN Library** | Real GaN MOSFET SPICE models |

---

## 📜 License

- Simulation files and source code: **MIT License**
- Technical report: **CC BY 4.0**
