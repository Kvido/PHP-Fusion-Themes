$(function () {
    $(".dropdown").on("show.bs.dropdown", function () {$(this).find(".dropdown-menu").first().stop(true, true).slideDown(200);});
    $(".dropdown").on("hide.bs.dropdown", function () {$(this).find(".dropdown-menu").first().stop(true, true).slideUp(100);});

    $("#backtotop").on("click", function (e) {
        e.preventDefault();
        $("html, body").animate({scrollTop: 0}, 200);
    });

    $("#toggle-leftmenu").on("click", function (e) {
        e.preventDefault();
        $("body").toggleClass("leftmenu-toggled");
    });

    $(".overlay").bind("click", function () {
        $("body").removeClass("leftmenu-toggled");
    });

    $("#main-menu").affix({
        offset: {
            top: $(".theme-header").outerHeight()
        }
    });
});
