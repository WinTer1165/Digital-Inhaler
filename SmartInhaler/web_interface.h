//web_interface.h
#ifndef WEB_INTERFACE_H
#define WEB_INTERFACE_H

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Smart Inhaler Control Panel</title>
    <link rel="apple-touch-icon" sizes="128x128" href="https://cdn-icons-png.flaticon.com/512/288/288222.png">
    <link rel="icon" type="image/svg+xml" href="data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 64 64'%3E%3Crect x='20' y='8' width='24' height='40' rx='4' fill='%230066cc'/%3E%3Crect x='24' y='4' width='16' height='8' rx='2' fill='%233399ff'/%3E%3Crect x='28' y='48' width='8' height='12' rx='2' fill='%230066cc'/%3E%3Ccircle cx='32' cy='28' r='6' fill='%23ffffff'/%3E%3C/svg%3E">
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        :root {
            --primary-blue: #0066cc;
            --secondary-blue: #004499;
            --accent-blue: #3399ff;
            --dark-bg: #0a0a0a;
            --card-bg: #111111;
            --border-color: rgba(0, 102, 204, 0.3);
            --text-primary: #ffffff;
            --text-secondary: #b0b0b0;
            --success: #00cc66;
            --warning: #ff9933;
            --danger: #ff3333;
        }

        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Oxygen, Ubuntu, sans-serif;
            background: linear-gradient(135deg, var(--dark-bg) 0%, #0d1117 100%);
            color: var(--text-primary);
            min-height: 100vh;
            padding: 20px;
            line-height: 1.6;
        }

        .container {
            max-width: 1400px;
            margin: 0 auto;
        }

        header {
            background: var(--card-bg);
            border: 1px solid var(--border-color);
            border-radius: 12px;
            padding: 25px;
            margin-bottom: 30px;
            box-shadow: 0 4px 20px rgba(0, 102, 204, 0.1);
        }

        .header-content {
            display: flex;
            justify-content: space-between;
            align-items: center;
            flex-wrap: wrap;
            gap: 20px;
        }

        h1 {
            color: var(--accent-blue);
            font-size: 2.2em;
            font-weight: 300;
            letter-spacing: -0.5px;
        }

        .device-info {
            display: flex;
            gap: 20px;
            align-items: center;
            font-size: 0.9em;
            color: var(--text-secondary);
        }

        .status-indicator {
            display: flex;
            align-items: center;
            gap: 8px;
            padding: 8px 16px;
            background: rgba(0, 204, 102, 0.1);
            border: 1px solid var(--success);
            border-radius: 20px;
        }

        .status-dot {
            width: 8px;
            height: 8px;
            border-radius: 50%;
            background: var(--success);
            animation: pulse 2s infinite;
        }

        .status-indicator.offline {
            background: rgba(255, 51, 51, 0.1);
            border-color: var(--danger);
        }

        .status-indicator.offline .status-dot {
            background: var(--danger);
            animation: none;
        }

        @keyframes pulse {
            0%, 100% { opacity: 1; }
            50% { opacity: 0.5; }
        }

        .dashboard {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(350px, 1fr));
            gap: 25px;
            margin-bottom: 30px;
        }

        .card {
            background: var(--card-bg);
            border: 1px solid var(--border-color);
            border-radius: 12px;
            padding: 25px;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.3);
            transition: transform 0.2s, box-shadow 0.2s;
        }

        .card:hover {
            transform: translateY(-2px);
            box-shadow: 0 4px 20px rgba(0, 102, 204, 0.2);
        }

        .card-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 20px;
            padding-bottom: 15px;
            border-bottom: 1px solid rgba(255, 255, 255, 0.1);
        }

        .card-title {
            font-size: 1.3em;
            color: var(--accent-blue);
            font-weight: 400;
        }

        .card-icon {
            width: 40px;
            height: 40px;
            background: linear-gradient(135deg, var(--primary-blue), var(--secondary-blue));
            border-radius: 10px;
            display: flex;
            align-items: center;
            justify-content: center;
        }

        .card-icon svg {
            width: 24px;
            height: 24px;
            fill: white;
        }

        .puff-display {
            text-align: center;
            padding: 30px 0;
        }

        .puff-count-large {
            font-size: 5em;
            font-weight: 200;
            background: linear-gradient(135deg, var(--accent-blue), var(--primary-blue));
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            margin: 10px 0;
            line-height: 1;
        }

        .puff-label {
            color: var(--text-secondary);
            font-size: 0.9em;
            text-transform: uppercase;
            letter-spacing: 2px;
        }

        .progress-container {
            margin: 25px 0;
        }

        .progress-bar {
            height: 8px;
            background: rgba(255, 255, 255, 0.05);
            border-radius: 4px;
            overflow: hidden;
            margin: 10px 0;
        }

        .progress-fill {
            height: 100%;
            background: linear-gradient(90deg, var(--primary-blue), var(--accent-blue));
            transition: width 0.5s ease;
            border-radius: 4px;
        }

        .progress-info {
            display: flex;
            justify-content: space-between;
            font-size: 0.85em;
            color: var(--text-secondary);
        }

        .metric-grid {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 15px;
        }

        .metric {
            background: rgba(0, 102, 204, 0.05);
            border: 1px solid rgba(0, 102, 204, 0.2);
            border-radius: 8px;
            padding: 15px;
            transition: background 0.2s;
        }

        .metric:hover {
            background: rgba(0, 102, 204, 0.1);
        }

        .metric-label {
            color: var(--text-secondary);
            font-size: 0.85em;
            margin-bottom: 5px;
        }

        .metric-value {
            font-size: 1.8em;
            color: var(--accent-blue);
            font-weight: 300;
        }

        .metric-unit {
            font-size: 0.6em;
            color: var(--text-secondary);
            margin-left: 4px;
        }

        .sensor-grid {
            display: grid;
            grid-template-columns: repeat(2, 1fr);
            gap: 15px;
        }

        .button-group {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(140px, 1fr));
            gap: 12px;
            margin-top: 20px;
        }

        button {
            background: linear-gradient(135deg, var(--primary-blue), var(--secondary-blue));
            color: white;
            border: none;
            padding: 12px 20px;
            border-radius: 8px;
            font-size: 0.95em;
            cursor: pointer;
            transition: all 0.3s;
            font-weight: 500;
            letter-spacing: 0.5px;
            position: relative;
            overflow: hidden;
        }

        button::before {
            content: '';
            position: absolute;
            top: 50%;
            left: 50%;
            width: 0;
            height: 0;
            border-radius: 50%;
            background: rgba(255, 255, 255, 0.2);
            transform: translate(-50%, -50%);
            transition: width 0.6s, height 0.6s;
        }

        button:hover::before {
            width: 300px;
            height: 300px;
        }

        button:hover {
            transform: translateY(-2px);
            box-shadow: 0 5px 20px rgba(0, 102, 204, 0.4);
        }

        button:active {
            transform: translateY(0);
        }

        button.danger {
            background: linear-gradient(135deg, var(--danger), #cc0000);
        }

        button.success {
            background: linear-gradient(135deg, var(--success), #009944);
        }

        .input-group {
            margin: 15px 0;
        }

        label {
            display: block;
            color: var(--text-secondary);
            font-size: 0.9em;
            margin-bottom: 8px;
        }

        input[type="time"],
        input[type="text"],
        input[type="number"],
        select {
            width: 100%;
            background: rgba(255, 255, 255, 0.05);
            border: 1px solid rgba(0, 102, 204, 0.3);
            color: var(--text-primary);
            padding: 10px 12px;
            border-radius: 6px;
            font-size: 0.95em;
            transition: all 0.3s;
        }

        input:focus, select:focus {
            outline: none;
            border-color: var(--accent-blue);
            background: rgba(0, 102, 204, 0.05);
            box-shadow: 0 0 0 3px rgba(0, 102, 204, 0.1);
        }

        .reminder-list {
            max-height: 250px;
            overflow-y: auto;
            margin: 15px 0;
        }

        .reminder-item {
            display: flex;
            justify-content: space-between;
            align-items: center;
            padding: 12px;
            background: rgba(0, 102, 204, 0.05);
            border: 1px solid rgba(0, 102, 204, 0.2);
            border-radius: 6px;
            margin-bottom: 10px;
            transition: background 0.2s;
        }

        .reminder-item:hover {
            background: rgba(0, 102, 204, 0.1);
        }

        .reminder-time {
            font-weight: 500;
            color: var(--accent-blue);
        }

        .reminder-label {
            color: var(--text-secondary);
            margin-left: 15px;
        }

        .alert {
            position: fixed;
            top: 30px;
            right: 30px;
            min-width: 300px;
            padding: 16px 20px;
            background: var(--card-bg);
            border: 1px solid var(--accent-blue);
            border-radius: 8px;
            box-shadow: 0 5px 20px rgba(0, 0, 0, 0.5);
            animation: slideIn 0.3s ease-out;
            z-index: 1000;
        }

        .alert-header {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 8px;
        }

        .alert-title {
            font-weight: 500;
            color: var(--accent-blue);
        }

        .alert-message {
            color: var(--text-secondary);
            font-size: 0.9em;
        }

        .alert.success {
            border-color: var(--success);
        }

        .alert.success .alert-title {
            color: var(--success);
        }

        .alert.warning {
            border-color: var(--warning);
        }

        .alert.warning .alert-title {
            color: var(--warning);
        }

        .alert.danger {
            border-color: var(--danger);
        }

        .alert.danger .alert-title {
            color: var(--danger);
        }

        @keyframes slideIn {
            from {
                transform: translateX(400px);
                opacity: 0;
            }
            to {
                transform: translateX(0);
                opacity: 1;
            }
        }

        .air-quality-indicator {
            display: flex;
            align-items: center;
            gap: 10px;
        }

        .air-quality-badge {
            padding: 4px 12px;
            border-radius: 20px;
            font-size: 0.85em;
            font-weight: 500;
        }

        .air-quality-badge.good {
            background: rgba(0, 204, 102, 0.2);
            color: var(--success);
            border: 1px solid var(--success);
        }

        .air-quality-badge.moderate {
            background: rgba(255, 153, 51, 0.2);
            color: var(--warning);
            border: 1px solid var(--warning);
        }

        .air-quality-badge.poor {
            background: rgba(255, 51, 51, 0.2);
            color: var(--danger);
            border: 1px solid var(--danger);
        }

        .risk-assessment {
            margin-top: 20px;
            padding: 15px;
            background: rgba(0, 102, 204, 0.05);
            border: 1px solid rgba(0, 102, 204, 0.2);
            border-radius: 8px;
        }

        .risk-level {
            display: flex;
            align-items: center;
            gap: 10px;
            margin-top: 10px;
        }

        .risk-indicator {
            width: 100%;
            height: 30px;
            background: linear-gradient(90deg, 
                var(--success) 0%, 
                var(--success) 33%, 
                var(--warning) 33%, 
                var(--warning) 66%, 
                var(--danger) 66%, 
                var(--danger) 100%);
            border-radius: 15px;
            position: relative;
        }

        .risk-pointer {
            position: absolute;
            top: -5px;
            width: 40px;
            height: 40px;
            background: var(--card-bg);
            border: 2px solid var(--accent-blue);
            border-radius: 50%;
            display: flex;
            align-items: center;
            justify-content: center;
            font-weight: bold;
            font-size: 0.9em;
            transition: left 0.5s ease;
        }

        .chart-container {
            margin-top: 20px;
            height: 250px;
            position: relative;
        }

        #usageChart {
            width: 100%;
            height: 100%;
        }

        @media (max-width: 768px) {
            .container {
                padding: 10px;
            }
            
            h1 {
                font-size: 1.6em;
            }
            
            .dashboard {
                grid-template-columns: 1fr;
                gap: 15px;
            }
            
            .header-content {
                flex-direction: column;
                align-items: flex-start;
            }
            
            .metric-grid,
            .sensor-grid {
                grid-template-columns: 1fr;
            }
            
            .puff-count-large {
                font-size: 3.5em;
            }
            
            .alert {
                right: 10px;
                left: 10px;
                min-width: auto;
            }
        }

        ::-webkit-scrollbar {
            width: 8px;
            height: 8px;
        }

        ::-webkit-scrollbar-track {
            background: rgba(0, 0, 0, 0.3);
            border-radius: 4px;
        }

        ::-webkit-scrollbar-thumb {
            background: var(--primary-blue);
            border-radius: 4px;
        }

        ::-webkit-scrollbar-thumb:hover {
            background: var(--accent-blue);
        }
    </style>
</head>
<body>
    <div class="container">
        <header>
            <div class="header-content">
                <div>
                    <h1>Smart Inhaler Control Panel</h1>
                    <div class="device-info">
                        <span>Device ID: <strong id="deviceId">INH-001</strong></span>
                        <span>IP: <strong id="deviceIp">---.---.---.---</strong></span>
                    </div>
                </div>
                <div class="status-indicator" id="connectionStatus">
                    <span class="status-dot"></span>
                    <span>Connected</span>
                </div>
            </div>
        </header>

        <div class="dashboard">
            <!-- Main Puff Counter -->
            <div class="card">
                <div class="card-header">
                    <h2 class="card-title">Puff Tracking</h2>
                    <div class="card-icon">
                        <svg viewBox="0 0 24 24">
                            <path d="M3,12H7L10,9L13,12L16,9L19,12H21V14H18L16,12L13,15L10,12L7,15L3,11V12Z"/>
                        </svg>
                    </div>
                </div>
                <div class="puff-display">
                    <div class="puff-label">Total Puffs</div>
                    <div class="puff-count-large" id="totalPuffs">0</div>
                </div>
                <div class="progress-container">
                    <div class="progress-bar">
                        <div class="progress-fill" id="puffProgress" style="width: 0%"></div>
                    </div>
                    <div class="progress-info">
                        <span>0%</span>
                        <span id="puffRatio">0 / 200</span>
                    </div>
                </div>
                <div class="metric-grid">
                    <div class="metric">
                        <div class="metric-label">Today's Usage</div>
                        <div class="metric-value" id="dailyPuffs">0</div>
                    </div>
                    <div class="metric">
                        <div class="metric-label">Remaining</div>
                        <div class="metric-value" id="remainingPuffs">200</div>
                    </div>
                </div>
            </div>

            <!-- Environmental Monitoring -->
            <div class="card">
                <div class="card-header">
                    <h2 class="card-title">Environmental Monitoring</h2>
                    <div class="card-icon">
                        <svg viewBox="0 0 24 24">
                            <path d="M14.5,17C15.88,17 17,15.88 17,14.5V10C17,8.62 15.88,7.5 14.5,7.5C13.12,7.5 12,8.62 12,10V14.5C12,15.88 13.12,17 14.5,17M9,11C9,7.97 11.03,5.67 13.94,5.16V2H16.06V5.16C18.97,5.67 21,7.97 21,11H18.5C18.5,8.79 16.71,7 14.5,7C12.29,7 10.5,8.79 10.5,11V15C10.5,17.21 12.29,19 14.5,19C16.71,19 18.5,17.21 18.5,15H21C21,18.03 18.97,20.33 16.06,20.84V24H13.94V20.84C11.03,20.33 9,18.03 9,15V11Z"/>
                        </svg>
                    </div>
                </div>
                <div class="sensor-grid">
                    <div class="metric">
                        <div class="metric-label">Temperature</div>
                        <div class="metric-value">
                            <span id="temperature">--</span>
                            <span class="metric-unit">°C</span>
                        </div>
                    </div>
                    <div class="metric">
                        <div class="metric-label">Humidity</div>
                        <div class="metric-value">
                            <span id="humidity">--</span>
                            <span class="metric-unit">%</span>
                        </div>
                    </div>
                    <div class="metric">
                        <div class="metric-label">Air Quality</div>
                        <div class="metric-value">
                            <div class="air-quality-indicator">
                                <span id="airQualityScore">--</span>
                                <span class="air-quality-badge" id="airQualityBadge">--</span>
                            </div>
                        </div>
                    </div>
                    <div class="metric">
                        <div class="metric-label">Pressure</div>
                        <div class="metric-value">
                            <span id="pressure">--</span>
                            <span class="metric-unit">hPa</span>
                        </div>
                    </div>
                </div>
                <div class="risk-assessment">
                    <div style="color: var(--text-secondary); font-size: 0.9em; margin-bottom: 5px;">
                        Asthma Attack Risk
                    </div>
                    <div class="risk-level">
                        <div class="risk-indicator">
                            <div class="risk-pointer" id="riskPointer">
                                <span id="riskPercentage">0%</span>
                            </div>
                        </div>
                    </div>
                    <div style="display: flex; justify-content: space-between; margin-top: 10px; font-size: 0.8em; color: var(--text-secondary);">
                        <span>Low</span>
                        <span>Moderate</span>
                        <span>High</span>
                    </div>
                </div>
                <div style="margin-top: 15px; text-align: center; color: var(--text-secondary); font-size: 0.85em;">
                    Last Update: <span id="timestamp">--:--:--</span>
                </div>
            </div>

            <!-- Usage Graph -->
            <div class="card">
                <div class="card-header">
                    <h2 class="card-title">Usage History (Last 7 Days)</h2>
                    <div class="card-icon">
                        <svg viewBox="0 0 24 24">
                            <path d="M22,21H2V3H4V19H6V10H10V19H12V6H16V19H18V14H22V21Z"/>
                        </svg>
                    </div>
                </div>
                <div class="chart-container">
                    <canvas id="usageChart"></canvas>
                </div>
            </div>

            <!-- Device Controls -->
            <div class="card">
                <div class="card-header">
                    <h2 class="card-title">Device Controls</h2>
                    <div class="card-icon">
                        <svg viewBox="0 0 24 24">
                            <path d="M12,15.5A3.5,3.5 0 0,1 8.5,12A3.5,3.5 0 0,1 12,8.5A3.5,3.5 0 0,1 15.5,12A3.5,3.5 0 0,1 12,15.5M19.43,12.97C19.47,12.65 19.5,12.33 19.5,12C19.5,11.67 19.47,11.34 19.43,11L21.54,9.37C21.73,9.22 21.78,8.95 21.66,8.73L19.66,5.27C19.54,5.05 19.27,4.96 19.05,5.05L16.56,6.05C16.04,5.66 15.5,5.32 14.87,5.07L14.5,2.42C14.46,2.18 14.25,2 14,2H10C9.75,2 9.54,2.18 9.5,2.42L9.13,5.07C8.5,5.32 7.96,5.66 7.44,6.05L4.95,5.05C4.73,4.96 4.46,5.05 4.34,5.27L2.34,8.73C2.21,8.95 2.27,9.22 2.46,9.37L4.57,11C4.53,11.34 4.5,11.67 4.5,12C4.5,12.33 4.53,12.65 4.57,12.97L2.46,14.63C2.27,14.78 2.21,15.05 2.34,15.27L4.34,18.73C4.46,18.95 4.73,19.03 4.95,18.95L7.44,17.94C7.96,18.34 8.5,18.68 9.13,18.93L9.5,21.58C9.54,21.82 9.75,22 10,22H14C14.25,22 14.46,21.82 14.5,21.58L14.87,18.93C15.5,18.67 16.04,18.34 16.56,17.94L19.05,18.95C19.27,19.03 19.54,18.95 19.66,18.73L21.66,15.27C21.78,15.05 21.73,14.78 21.54,14.63L19.43,12.97Z"/>
                        </svg>
                    </div>
                </div>
                <div class="button-group">
                    <button onclick="findDevice()">Find Device</button>
                    <button onclick="refreshData()" class="success">Refresh Data</button>
                    <button onclick="resetPuffs()" class="danger">Reset Counter</button>
                    <button onclick="testHardware()">Test Hardware</button>
                </div>
                <div class="input-group">
                    <label for="maxPuffsInput">Maximum Puffs per Inhaler</label>
                    <input type="number" id="maxPuffsInput" value="200" min="50" max="500">
                    <button onclick="setMaxPuffs()" style="width: 100%; margin-top: 10px;">Update Limit</button>
                </div>
            </div>

            <!-- Medication Reminders -->
            <div class="card">
                <div class="card-header">
                    <h2 class="card-title">Medication Reminders</h2>
                    <div class="card-icon">
                        <svg viewBox="0 0 24 24">
                            <path d="M12,20A7,7 0 0,1 5,13A7,7 0 0,1 12,6A7,7 0 0,1 19,13A7,7 0 0,1 12,20M12,4A9,9 0 0,0 3,13A9,9 0 0,0 12,22A9,9 0 0,0 21,13A9,9 0 0,0 12,4M12.5,8H11V14L15.75,16.85L16.5,15.62L12.5,13.25V8M7.88,3.39L6.6,1.86L2,5.71L3.29,7.24L7.88,3.39M22,5.72L17.4,1.86L16.11,3.39L20.71,7.25L22,5.72Z"/>
                        </svg>
                    </div>
                </div>
                <div class="reminder-list" id="reminderList">
                    <div style="text-align: center; color: var(--text-secondary); padding: 20px;">
                        No reminders set
                    </div>
                </div>
                <div class="input-group">
                    <label for="reminderTime">Reminder Time</label>
                    <input type="time" id="reminderTime">
                </div>
                <div class="input-group">
                    <label for="reminderLabel">Description</label>
                    <input type="text" id="reminderLabel" placeholder="e.g., Morning dose">
                </div>
                <button onclick="addReminder()" style="width: 100%;">Add Reminder</button>
            </div>
        </div>
    </div>

    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <script>
        let ws;
        let reconnectInterval;
        let reminders = [];
        let usageChart;
        let deviceData = {
            totalPuffs: 0,
            maxPuffs: 200,
            dailyPuffs: 0,
            usageHistory: []
        };
        
        function connectWebSocket() {
            const wsUrl = `ws://${window.location.hostname}:81`;
            ws = new WebSocket(wsUrl);
            
            ws.onopen = function() {
                console.log('WebSocket connected');
                updateConnectionStatus(true);
                clearInterval(reconnectInterval);
                ws.send(JSON.stringify({command: 'getData'}));
                ws.send(JSON.stringify({command: 'getReminders'}));
                ws.send(JSON.stringify({command: 'getHistory'}));
            };
            
            ws.onmessage = function(event) {
                const data = JSON.parse(event.data);
                handleMessage(data);
            };
            
            ws.onclose = function() {
                console.log('WebSocket disconnected');
                updateConnectionStatus(false);
                reconnectInterval = setInterval(connectWebSocket, 3000);
            };
            
            ws.onerror = function(error) {
                console.error('WebSocket error:', error);
                updateConnectionStatus(false);
            };
        }
        
        function updateConnectionStatus(connected) {
            const statusEl = document.getElementById('connectionStatus');
            if (connected) {
                statusEl.className = 'status-indicator';
                statusEl.innerHTML = '<span class="status-dot"></span><span>Connected</span>';
            } else {
                statusEl.className = 'status-indicator offline';
                statusEl.innerHTML = '<span class="status-dot"></span><span>Offline</span>';
            }
        }
        
        function handleMessage(data) {
            switch(data.type) {
                case 'sensorData':
                    updateSensorData(data);
                    break;
                case 'puffDetected':
                    handlePuffDetected(data);
                    break;
                case 'reminder':
                    showAlert('Medication Reminder', data.label, 'warning');
                    break;
                case 'maxPuffsReached':
                    showAlert('Maximum Puffs Reached', 'Please replace the inhaler cartridge', 'danger');
                    break;
                case 'reminders':
                    updateRemindersFromDevice(data.reminders);
                    break;
                case 'usageHistory':
                    updateUsageChart(data.history);
                    break;
            }
        }
        
        function updateSensorData(data) {
            document.getElementById('deviceId').textContent = data.deviceId || 'INH-001';
            document.getElementById('deviceIp').textContent = data.ip || window.location.hostname;
            
            deviceData.totalPuffs = data.totalPuffs;
            deviceData.maxPuffs = data.maxPuffs;
            deviceData.dailyPuffs = data.dailyPuffs;
            
            document.getElementById('totalPuffs').textContent = data.totalPuffs;
            document.getElementById('dailyPuffs').textContent = data.dailyPuffs;
            document.getElementById('remainingPuffs').textContent = Math.max(0, data.maxPuffs - data.totalPuffs);
            
            const percentage = Math.min(100, (data.totalPuffs / data.maxPuffs) * 100);
            const progressBar = document.getElementById('puffProgress');
            progressBar.style.width = percentage + '%';
            
            if (percentage > 90) {
                progressBar.style.background = 'linear-gradient(90deg, #ff3333, #cc0000)';
            } else if (percentage > 75) {
                progressBar.style.background = 'linear-gradient(90deg, #ff9933, #ff6600)';
            } else {
                progressBar.style.background = 'linear-gradient(90deg, var(--primary-blue), var(--accent-blue))';
            }
            
            document.querySelector('.progress-info span:first-child').textContent = `${percentage.toFixed(1)}%`;
            document.getElementById('puffRatio').textContent = `${data.totalPuffs} / ${data.maxPuffs}`;
            
            document.getElementById('temperature').textContent = data.temperature.toFixed(1);
            document.getElementById('humidity').textContent = data.humidity.toFixed(0);
            document.getElementById('pressure').textContent = data.pressure.toFixed(0);
            
            // Update Air Quality Display
            const aqScore = data.airQuality;
            const aqScoreEl = document.getElementById('airQualityScore');
            const aqBadgeEl = document.getElementById('airQualityBadge');
            
            aqScoreEl.textContent = aqScore;
            
            if (aqScore >= 80) {
                aqBadgeEl.textContent = 'Good';
                aqBadgeEl.className = 'air-quality-badge good';
            } else if (aqScore >= 60) {
                aqBadgeEl.textContent = 'Moderate';
                aqBadgeEl.className = 'air-quality-badge moderate';
            } else {
                aqBadgeEl.textContent = 'Poor';
                aqBadgeEl.className = 'air-quality-badge poor';
            }
            
            // Calculate Asthma Attack Risk
            const risk = calculateAsthmaRisk(data.temperature, data.humidity, aqScore, data.pressure);
            updateRiskIndicator(risk);
            
            document.getElementById('timestamp').textContent = data.timestamp;
        }
        
        function calculateAsthmaRisk(temp, humidity, airQuality, pressure) {
            let riskScore = 0;
            
            // Temperature factor - ideal: 18-22°C
            if (temp < 10 || temp > 30) {
                riskScore += 25;
            } else if (temp < 15 || temp > 25) {
                riskScore += 15;
            } else if (temp < 18 || temp > 22) {
                riskScore += 5;
            }
            
            // Humidity factor - ideal: 40-60%
            if (humidity < 30 || humidity > 70) {
                riskScore += 25;
            } else if (humidity < 40 || humidity > 60) {
                riskScore += 10;
            }
            
            // Air quality factor
            if (airQuality < 60) {
                riskScore += 30;
            } else if (airQuality < 80) {
                riskScore += 15;
            }
            
            // Pressure factor (rapid changes increase risk)
            if (pressure < 990 || pressure > 1030) {
                riskScore += 20;
            } else if (pressure < 1000 || pressure > 1020) {
                riskScore += 10;
            }
            
            return Math.min(100, riskScore);
        }
        
        function updateRiskIndicator(risk) {
            const pointer = document.getElementById('riskPointer');
            const percentage = document.getElementById('riskPercentage');
            
            pointer.style.left = `calc(${risk}% - 20px)`;
            percentage.textContent = `${risk}%`;
            
            if (risk <= 33) {
                pointer.style.borderColor = 'var(--success)';
            } else if (risk <= 66) {
                pointer.style.borderColor = 'var(--warning)';
            } else {
                pointer.style.borderColor = 'var(--danger)';
            }
        }
        
        function handlePuffDetected(data) {
            updateSensorData(data);
            showAlert('Puff Detected', `Total puffs: ${data.totalPuffs}`, 'success');
            
            const counter = document.getElementById('totalPuffs');
            counter.style.animation = 'none';
            setTimeout(() => {
                counter.style.animation = 'pulse 0.5s';
            }, 10);
        }
        
        function showAlert(title, message, type = 'info') {
            const alert = document.createElement('div');
            alert.className = `alert ${type}`;
            alert.innerHTML = `
                <div class="alert-header">
                    <div class="alert-title">${title}</div>
                    <span style="cursor: pointer;" onclick="this.parentElement.parentElement.remove()">×</span>
                </div>
                <div class="alert-message">${message}</div>
            `;
            document.body.appendChild(alert);
            
            setTimeout(() => {
                alert.style.animation = 'slideIn 0.3s reverse';
                setTimeout(() => alert.remove(), 300);
            }, 5000);
        }
        
        function findDevice() {
            if (ws && ws.readyState === WebSocket.OPEN) {
                ws.send(JSON.stringify({command: 'findDevice'}));
                showAlert('Finding Device', 'The inhaler will beep and vibrate for 30 seconds', 'info');
            }
        }
        
        function testHardware() {
            if (ws && ws.readyState === WebSocket.OPEN) {
                ws.send(JSON.stringify({command: 'testHardware'}));
                showAlert('Testing Hardware', 'The device will beep and vibrate briefly', 'info');
            }
        }
        
        function resetPuffs() {
            if (confirm('Are you sure you want to reset the puff counter? This action cannot be undone.')) {
                if (ws && ws.readyState === WebSocket.OPEN) {
                    ws.send(JSON.stringify({command: 'resetPuffs'}));
                    showAlert('Counter Reset', 'The puff counter has been reset to 0', 'success');
                }
            }
        }
        
        function refreshData() {
            if (ws && ws.readyState === WebSocket.OPEN) {
                ws.send(JSON.stringify({command: 'getData'}));
                ws.send(JSON.stringify({command: 'getHistory'}));
                showAlert('Data Refreshed', 'All sensor data has been updated', 'success');
            }
        }
        
        function setMaxPuffs() {
            const maxPuffs = document.getElementById('maxPuffsInput').value;
            if (ws && ws.readyState === WebSocket.OPEN) {
                ws.send(JSON.stringify({
                    command: 'setMaxPuffs',
                    maxPuffs: parseInt(maxPuffs)
                }));
                showAlert('Limit Updated', `Maximum puffs set to ${maxPuffs}`, 'success');
            }
        }
        
        function addReminder() {
            const time = document.getElementById('reminderTime').value;
            const label = document.getElementById('reminderLabel').value;
            
            if (time && label) {
                const [hour, minute] = time.split(':');
                const index = reminders.length;
                
                if (index >= 5) {
                    showAlert('Limit Reached', 'Maximum 5 reminders allowed', 'warning');
                    return;
                }
                
                if (ws && ws.readyState === WebSocket.OPEN) {
                    ws.send(JSON.stringify({
                        command: 'setReminder',
                        index: index,
                        hour: parseInt(hour),
                        minute: parseInt(minute),
                        label: label
                    }));
                    
                    reminders.push({time, label});
                    updateReminderList();
                    
                    document.getElementById('reminderTime').value = '';
                    document.getElementById('reminderLabel').value = '';
                    
                    showAlert('Reminder Added', `Reminder set for ${time}`, 'success');
                }
            } else {
                showAlert('Invalid Input', 'Please enter both time and description', 'warning');
            }
        }
        
        function deleteReminder(index) {
            if (ws && ws.readyState === WebSocket.OPEN) {
                ws.send(JSON.stringify({
                    command: 'deleteReminder',
                    index: index
                }));
                
                reminders.splice(index, 1);
                updateReminderList();
                showAlert('Reminder Deleted', 'The reminder has been removed', 'success');
            }
        }
        
        function updateReminderList() {
            const list = document.getElementById('reminderList');
            
            if (reminders.length === 0) {
                list.innerHTML = '<div style="text-align: center; color: var(--text-secondary); padding: 20px;">No reminders set</div>';
                return;
            }
            
            list.innerHTML = '';
            reminders.forEach((reminder, index) => {
                const item = document.createElement('div');
                item.className = 'reminder-item';
                item.innerHTML = `
                    <div>
                        <span class="reminder-time">${reminder.time}</span>
                        <span class="reminder-label">${reminder.label}</span>
                    </div>
                    <button onclick="deleteReminder(${index})" style="padding: 5px 10px; font-size: 0.85em;">Remove</button>
                `;
                list.appendChild(item);
            });
        }
        
        function updateRemindersFromDevice(deviceReminders) {
            reminders = deviceReminders;
            updateReminderList();
        }
        
        function initChart() {
            const ctx = document.getElementById('usageChart').getContext('2d');
            usageChart = new Chart(ctx, {
                type: 'line',
                data: {
                    labels: [],
                    datasets: [{
                        label: 'Daily Puffs',
                        data: [],
                        borderColor: '#3399ff',
                        backgroundColor: 'rgba(51, 153, 255, 0.1)',
                        borderWidth: 2,
                        tension: 0.4,
                        pointRadius: 4,
                        pointBackgroundColor: '#3399ff',
                        pointBorderColor: '#fff',
                        pointBorderWidth: 2
                    }]
                },
                options: {
                    responsive: true,
                    maintainAspectRatio: false,
                    plugins: {
                        legend: {
                            display: false
                        },
                        tooltip: {
                            backgroundColor: 'rgba(0, 0, 0, 0.8)',
                            padding: 12,
                            cornerRadius: 8,
                            titleColor: '#3399ff',
                            bodyColor: '#ffffff',
                            borderColor: '#3399ff',
                            borderWidth: 1
                        }
                    },
                    scales: {
                        x: {
                            grid: {
                                color: 'rgba(255, 255, 255, 0.05)',
                                borderColor: 'rgba(255, 255, 255, 0.1)'
                            },
                            ticks: {
                                color: '#b0b0b0'
                            }
                        },
                        y: {
                            beginAtZero: true,
                            grid: {
                                color: 'rgba(255, 255, 255, 0.05)',
                                borderColor: 'rgba(255, 255, 255, 0.1)'
                            },
                            ticks: {
                                color: '#b0b0b0',
                                stepSize: 1
                            }
                        }
                    }
                }
            });
        }
        
        function updateUsageChart(history) {
            if (!usageChart) {
                initChart();
            }
            
            const labels = history.map(h => `${h.month}/${h.day}`);
            const data = history.map(h => h.puffs);
            
            usageChart.data.labels = labels;
            usageChart.data.datasets[0].data = data;
            usageChart.update();
        }
        
        // Initialize
        connectWebSocket();
        updateReminderList();
        initChart();
        
        // Auto-refresh data every 10 seconds
        setInterval(() => {
            if (ws && ws.readyState === WebSocket.OPEN) {
                ws.send(JSON.stringify({command: 'getData'}));
            }
        }, 10000);
        
        // Fetch initial status via HTTP as fallback
        fetch('/status')
            .then(response => response.json())
            .then(data => {
                if (data.connected) {
                    updateSensorData(data);
                }
            })
            .catch(error => console.error('Error fetching initial status:', error));
    </script>
</body>
</html>
)=====";

#endif