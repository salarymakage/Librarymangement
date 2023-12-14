const cursor = document.querySelector('.cursor');
const cursorPoint = document.querySelector('.cursor__point');
const cursorCircle = document.querySelector('.cursor__circle');
const content = document.querySelector('.content');

document.body.addEventListener('mousemove', onMouseMove);
for (let i = 0; i < content.children.length; i++) {
    const element = content.children[i];
    element.addEventListener('mouseenter', onMouseHover);
    element.addEventListener('mouseleave', onMouseHoverOut);
}

function onMouseMove(e) {
    TweenMax.to(cursorPoint, 0.1, {
        x: e.clientX,
        y: e.clientY
    });

    // Adjust the speed factor as needed
    TweenMax.to(cursorCircle, 0.5, {
        x: e.clientX,
        y: e.clientY
    });

    // Check if cursor is near a button
    const buttons = document.querySelectorAll('.button');
    let isNearButton = false;
    buttons.forEach((button) => {
        const rect = button.getBoundingClientRect();
        const cursorX = e.clientX;
        const cursorY = e.clientY;

        if (
            cursorX >= rect.left &&
            cursorX <= rect.right &&
            cursorY >= rect.top &&
            cursorY <= rect.bottom
        ) {
            // Cursor is near a button, add the "near-button" class to cursor
            isNearButton = true;
        }
    });

    if (isNearButton) {
        cursor.classList.add('enlarged');
    } else {
        cursor.classList.remove('enlarged');
    }
}

function onMouseHover() {
    TweenMax.to(cursorPoint, 0.3, {
        scale: 1.5
    });

    TweenMax.to(cursorCircle, 0.3, {
        scale: 3
    });
}

function onMouseHoverOut() {
    TweenMax.to(cursorPoint, 0.3, {
        scale: 1
    });

    TweenMax.to(cursorCircle, 0.3, {
        scale: 1
    });
}
