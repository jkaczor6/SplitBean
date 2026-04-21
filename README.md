# SplitBean 🫘

A cooperative puzzle game for two players built in Unreal Engine 5, inspired by Portal and the Minecraft map *Two For One*. Both players must work together — and communicate — to solve each level. Neither can succeed alone.

---

## 🎮 Gameplay

SplitBean is a **2-player co-op puzzle game** where each level introduces a unique mechanic that requires coordination, communication, and trust between players. Players are separated into two color-coded sides — **red** and **blue** — and must cooperate to progress.

---

## 🧩 Levels

| # | Name | Description |
|---|------|-------------|
| 1 | **First Steps** | A simple platforming puzzle where pressure plates extend platforms for the other player. |
| 2 | **Double Trouble** | A more complex take on the pressure plate mechanic with multiple stages. |
| 3 | **Venetian Maze** | One player navigates a maze on the ground floor while the other watches from above through a one-way mirror and guides them. |
| 4 | **Hidden in Plain Sight** | Each player has a button camouflaged in the color of their walls. Both must find and press their button at the same moment to open the door. |
| 5 | **Sequence** | One player sees a randomized sequence on a display and must dictate it to the other, who presses the corresponding buttons in order. A wrong press reshuffles everything. |
| 6 | **Minefield** | A procedurally generated minefield. One player navigates it blind while the other sees a map of the safe path and must guide them across. |
| 7 | **Mirror Maze** | Two separate mazes — one player sees a mirrored top-down view of the other's maze on their wall via a live render target, and must navigate them to the exit. |

---

## 🛠️ Tech Stack

- **Engine:** Unreal Engine 5.7
- **Language:** C++
- **Multiplayer:** Online co-op (2 players, dedicated listen server)
- **Key UE5 features used:**
  - Replication & RPCs (Server, NetMulticast)
  - SceneCaptureComponent2D + Render Targets
  - TextRenderComponent
  - Enhanced Input System

---

## 🚀 Getting Started

### Prerequisites
- Unreal Engine 5.7
- Visual Studio 2022 (with C++ game development workload)

### Setup
```bash
git clone https://github.com/yourusername/SplitBean.git
```
1. Right-click `SplitBean.uproject` → **Generate Visual Studio project files**
2. Open `SplitBean.sln` in Visual Studio and build
3. Open `SplitBean.uproject` in Unreal Engine 5.7
4. Press **Play** with two players in the editor or package the game

---

## 🎯 About

SplitBean was developed as a portfolio project to demonstrate:
- Multiplayer game architecture in C++ with UE5
- Level design with asymmetric co-op mechanics
- Clean, self-written codebase (no Blueprint logic, no vibe coding)

---

## 🕹️ Play

The game is available on itch.io: [jkaczor6.itch.io/splitbean](https://jkaczor6.itch.io/splitbean)

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

---

## 📸 Screenshots & Trailer

*Coming soon.*
